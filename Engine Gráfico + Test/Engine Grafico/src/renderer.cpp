#include "glew.h"
#include "glfw3.h"
#include "renderer.h"

struct ShaderProgramSource
{
	string VertexSource;
	string FragmentSource;
};

unsigned int CompileShader(unsigned int type, const char* source)
{
	unsigned int id = glCreateShader(type);	 
	/// Crea un objeto shader vacio y devuelve un valor diferente de cero con el que puede ser referenciado, el tipo indica que tipo de shader se va a crear, sea de vertex,fragment, geometry, etc
	string sourceShaderCode;
	ifstream sourceShaderFile;
	sourceShaderFile.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		sourceShaderFile.open(source);
		stringstream sourceShaderStream;

		sourceShaderStream << sourceShaderFile.rdbuf();
		sourceShaderFile.close();

		sourceShaderCode = sourceShaderStream.str();
	}
	catch (ifstream::failure & e)
	{
		cout << "Error de lectura del shader" << endl;
	}

	const char* src = sourceShaderCode.c_str();

	glShaderSource(id, 1, &src, nullptr); // Reemplaza el codigo fuente de un shader object, los parametros son: El identificador del shader, camntidad de elementos en el string array, el array que contiene el codigo, el length del array
	glCompileShader(id);  /// Indispensable para el glUseProgram, Compila el codigo que est� guardado con el identificador que recibe de parametro

	return (id);

}

unsigned int  Renderer::CreateShader(const char* vertexShader, const char* fragmentShader)
{
	unsigned int program = glCreateProgram(); // crea un program object vacio
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);  /// Indispensable para el glUseProgram, se encarga de especificar la lista de cosas que van a ser linkeadas, 
	glAttachShader(program, fs);  /// Indispensable para el glUseProgram, basicamente dice cuales shaders tienen que linkearse con el programa al hacer el linkProgram

	glLinkProgram(program);  /// Indispensable para el glUseProgram, usa los shaders attacheados para crear un ejecutable que corra en el procesador, 
	//el estatus es guardado como parte del programa y es seteado en true si el programa fue linkeado sin errores y en false en caso contrario, se puede obtener con la funcion glGetProgram
	// Como resultado de un linkeo exitoso todas las variables definidas por usuario son inicializadas en 0 y cada variable es asignada a una posicion para poder ser llamada con glGetUniformLocation
	glValidateProgram(program); /// chequea para ver si el ejecutable que contiene el program puede ser ejecutado con el estado actual de OpenGL, la info va a quedar en un log para poder verificar el estado
	
	glDetachShader(program, vs);	
	glDetachShader(program, fs);	

	glDeleteShader(vs);  // borra el shader para que no se haga un obj, Libera la memoria e invalida el nombre asosiado al shader, basicamente invalida el create shader
	glDeleteShader(fs);	 // borra el shader para que no se haga un obj, al usar delete shader sin detachear, este es marcado para ser borrado luego de que deje de estar attacheado

	return program;
	//leer las funciones que empiezan con gl y hacer comentario de que hacen para tener a mano
}

Renderer::Renderer() {

}

Renderer::~Renderer() {
	//glDeleteProgram(shader);
}

void Renderer::Draw(unsigned int *indices, float *vertices, glm::mat4 _trsmatrix , int shapeType )
{		
	unsigned int model = glGetUniformLocation(shaderId,"trsmatrix");
	unsigned int projInd = glGetUniformLocation(shaderId, "proj");
	unsigned int viewInd = glGetUniformLocation(shaderId, "view");
	/// Devuelve la ubicacion de una variable uniforme, el primer parametro es el identificador del programa y el segundo el nombre de la variable que contiene esa ubicacion
	/// Devuelve un int que representa la ubicacion de una variable especifica dentro de un programa (el segundo parametro, "name") no puede contener espacios ni ser un struct, array de structs o un sub componente de un vector o matriz

	glUseProgram(shaderId); /// Instala un programa como parte recurrente del estado de renderizado, el parametro es el identificador del programa
	/// Requiere previamente haber, attacheado el shader, compilado el shader y linkeado el programa, atachear otro shader, desatachear este o borrar el shader durante la compilacion no van a afectar el estado actual del programa, pero si si es que volvemos a linkear

	glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(_trsmatrix));
	glUniformMatrix4fv(projInd, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
	glUniformMatrix4fv(viewInd, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));

	switch (shapeType)
	{
	case 0:
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 18, vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 3, indices, GL_STATIC_DRAW);
		break;
	case 1:
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * 24, vertices, GL_STATIC_DRAW);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * 6, indices, GL_STATIC_DRAW);
		break;
	default:
		break;
	}
	// le dice al buffer, donde guardar, que tanto espacio tiene disponible, que tiene que guardar y para que se va a usar 
	
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  //  hace el render de las primitivas en base a los del array
	//se usa si no tenes un index buffer, Dibuja segun un buffer, los parametros son: tipo de primitiva queres dibujar, cabtudad de elementos a ser renderizados, tipo de valores en el indice, desde donde comienza a leer la data
}



void Renderer::CreateShader()
{
	shaderId = CreateShader("../res/shader/Vertex.shader", "../res/shader/Fragment.shader");
	textureShaderId = CreateShader("../res/shader/TextureVertex.shader", "../res/shader/TextureFragment.shader");

}

void Renderer::initRender(unsigned int vao, unsigned int vbo, unsigned int ibo)
{
	GenerateVAO(vao);

	glGenBuffers(1, &vbo); /// Genera N cantidad de buffers en el primer parametro, el segundo parametro es en donde se almacenan los nombres de dichos buffers
	glBindBuffer(GL_ARRAY_BUFFER, vbo); // especifica a que buffer est� bindeando (primer parametro), segundo parametro es el nombre del buffer que estas bindeando
	//GL_ARRAY_BUFFER// ES PARA los vertices

	glGenBuffers(1, &ibo); //Genera X (en este caso 1) cantidad de buffers Buffer y le da un ID (en este caso el id buffer)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo); // selecciona el target (binding point buffer), el primer parametro dice a donde se va a conectar lo que determina que tipo de info tiene que haber en el buffer y el segundo es el ID
	//GL_ELEMENT_ARRAY_BUFFER es para los indices

	unsigned int verAttribute = glGetAttribLocation(shaderId, "position");	// devuelve la ubicacion de un atributo dentro de un programa y luego se lo asigna a una variable
	unsigned int colorAt = glGetAttribLocation(shaderId, "inColor");		//  Los parametros que se usan son el programa de donde estamos sacando el atribute, en estos casos los shaders, y el nombre del atributo

	// el glVertexAttribPointer es muy importante ya que espeficia como leer el buffer, como interpretar la data que ponemos adentro del mismo
	glVertexAttribPointer(verAttribute, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(0 * sizeof(float))); //index, tama�o del VERTEX , tipo de dato, si queremos que se normalice, stride (cuanto tiene que recorrer hasta el siguiente VERTEX, no al siguiente Attribute), stride al siguiente atributo
	glVertexAttribPointer(colorAt, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(3 * sizeof(float))); /// lee igual que el otro, pero arranca desde la pos 3 en lugar de la 0, ya que ah� empiezan los valores de RGB

	glEnableVertexAttribArray(verAttribute);  //Habilita y deshabilita los attributos del array vertex
	glEnableVertexAttribArray(colorAt);  //Habilita y deshabilita los attributos del array vertex

}



void Renderer::GenerateVAO(unsigned int& vao) {
	glGenVertexArrays(1, &vao); // genera N arrays de vertices y guarda sus nombres en el segundo parametro
	glBindVertexArray(vao);// le dice al vertex array cual es su nombre en caso de que no haya un vertex array object con ese nombre crea el vinculo entre el array y el nombre, si ya lo hay entonces rompe el vinculo previo 
}
void Renderer::BindVAO(unsigned int& vao) {
	glBindVertexArray(vao);
}
void Renderer::BindVBO(unsigned int& vbo, float* vertices, int verticesAmmount) {
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices) * verticesAmmount, vertices, GL_STATIC_DRAW);
}
void Renderer::BindEBO(unsigned int& ebo, unsigned int* indices, int indicesAmmount) {
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices) * indicesAmmount, indices, GL_STATIC_DRAW);
}
void Renderer::UnbindBuffers() {
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glUseProgram(0);
}
void Renderer::DeleteBuffers(unsigned int& vao, unsigned int& vbo, unsigned int& ebo) {
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ebo);
}

void Renderer::CreateAtribPointers(unsigned int shaderAttribIndex, int dataAmmount, int dataSize, int dataPosition) {
	glVertexAttribPointer(shaderAttribIndex, dataAmmount, GL_FLOAT, GL_FALSE, sizeof(float) * dataSize, (void*)(sizeof(float) * dataPosition));
	glEnableVertexAttribArray(shaderAttribIndex);
}

void Renderer::SetTexAttribPointer() {

	GLuint posAttrib = glGetAttribLocation(textureShaderId, "position");
	GLuint colorAttrib = glGetAttribLocation(textureShaderId, "inColor"); 
	GLuint texAttrib = glGetAttribLocation(textureShaderId, "uv");
	glUniform1i((glGetUniformLocation(textureShaderId, "thisTexture")), 0);
	CreateAtribPointers(posAttrib, 3, 8, 0);
	CreateAtribPointers(colorAttrib, 3, 8, 3);
	CreateAtribPointers(2, 2, 8, 6);    /// preguntar porque si pongo texAttrib en vez de 2 me manda numero gigante
}

void Renderer::DrawSprite(unsigned int& vao, unsigned int& vbo, float* vertices, int verticesAmmount, glm::mat4 model, unsigned int* indices) {
	BindVAO(vao);
	BindVBO(vbo, vertices, verticesAmmount);
	SetTexAttribPointer();

	unsigned int textureModel = glGetUniformLocation(textureShaderId, "trsmatrix");
	unsigned int projInd = glGetUniformLocation(textureShaderId, "proj");
	unsigned int viewInd = glGetUniformLocation(textureShaderId, "view");
	/// Devuelve la ubicacion de una variable uniforme, el primer parametro es el identificador del programa y el segundo el nombre de la variable que contiene esa ubicacion
	/// Devuelve un int que representa la ubicacion de una variable especifica dentro de un programa (el segundo parametro, "name") no puede contener espacios ni ser un struct, array de structs o un sub componente de un vector o matriz

	glUseProgram(textureShaderId); /// Instala un programa como parte recurrente del estado de renderizado, el parametro es el identificador del programa
	/// Requiere previamente haber, attacheado el shader, compilado el shader y linkeado el programa, atachear otro shader, desatachear este o borrar el shader durante la compilacion no van a afectar el estado actual del programa, pero si si es que volvemos a linkear

	glUniformMatrix4fv(textureModel, 1, GL_FALSE, glm::value_ptr(model));
	glUniformMatrix4fv(projInd, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));
	glUniformMatrix4fv(viewInd, 1, GL_FALSE, glm::value_ptr(glm::mat4(1)));

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	UnbindBuffers();
}
