//////////////////////////////////////////////////////////////////////////////
//
//  --- LoadShaders.cxx ---
//
//////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC
#include <GL/glut.h>
#include "LoadShaders.h"

//----------------------------------------------------------------------------

static const GLchar* ReadShader( const char* filename ) {
	FILE* infile = fopen(filename, "rb");
	if (!infile ) {
		fprintf (stderr, "Unable to open file ' %s'\n", filename);
		return NULL;
	}

	fseek(infile, 0, SEEK_END);
	int len = ftell(infile);
	fseek( infile, 0, SEEK_SET );


	GLchar* source = (GLchar*) malloc ((len+1) * sizeof (GLchar));

	fread( source, 1, len, infile);
	fclose( infile );

	source[len] = 0;

	return (const GLchar*) source;
}

//----------------------------------------------------------------------------

GLuint LoadShaders(ShaderInfo* shaders) {
	if (shaders == NULL ) {
		return 0;
	}

	GLuint program = glCreateProgram();

	ShaderInfo* entry = shaders;			// COUNTER

	while ( entry->type != GL_NONE ) {
		GLuint shader = glCreateShader(entry->type);
		entry->shader = shader;

		const GLchar* source = ReadShader(entry->filename);

		printf ("Leido: \n%s\n", source);

		if (source == NULL ) {
			for (entry = shaders; entry->type != GL_NONE; entry++) {
				glDeleteShader(entry->shader );
				entry->shader = 0;
			}
		return 0;
        	}

		glShaderSource(shader, 1, &source, NULL);
		free ((char*) source);

        	glCompileShader( shader );
	
		GLint compiled;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled) {
			GLsizei len;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
			GLchar log[len+1];
			glGetShaderInfoLog(shader, len, &len, log);
			fprintf (stderr, "Shader compilation failed:\n%s\n", log);
			return 0;
		}

		glAttachShader(program, shader);
	        entry++;
	}

    
	glLinkProgram( program );

	GLint linked;
	glGetProgramiv(program, GL_LINK_STATUS, &linked);
	if (!linked ) {
		GLsizei len;
		glGetProgramiv (program, GL_INFO_LOG_LENGTH, &len);
		GLchar log[len+1];
		glGetProgramInfoLog (program, len, &len, log);
		fprintf (stderr, "Shader linking failed:\n%s\n", log);

		for (entry = shaders; entry->type != GL_NONE; entry++) {
			glDeleteShader( entry->shader );
			entry->shader = 0;
		}
        
		return 0;
	}

	return program;
}

