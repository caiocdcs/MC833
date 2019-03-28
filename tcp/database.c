#include <string.h>

#include "database.h"

// Exemplo de perfil:
// Email: maria_silva@gmail.com
// Nome: Maria Sobrenome: Silva
// Foto: Imagem em JPEG, PNG, etc
// Residência: Campinas
// Formação Acadêmica: Ciência da Computação
// Habilidades: Análise de Dados, Internet das Coisas, Computação em Nuvem
// Experiência: (1) Estágio de 1 ano na Empresa X, onde trabalhei como analista de dados
//  (2) Trabalhei com IoT e Computação em Nuvem por 5 anos na Empresa Y 

profile profiles[] = {
	{
		.email = "sean_parkins@gmail.com",
		.name = "Sean Parkis",
		.photoURL = "",
		.city = "London",
		.course = "Music",
		.skill = "Piano, Guitar, Drums",
		.exp = "Play in the city theater","Play drums on a rock band"
	},
	{
		.email = "jane.doe@gmail.com",
		.name = "Jane Doe",
		.photoURL = "",
		.city = "Copenhagen",
		.course = "Architecture",
		.skill = "Graphics, 3D Modeling, Platforms",
		.exp = "Intern Architect","Affordable Housing Project"
	},
	{
		.email = "desiree@garrison.com",
		.name = "Desiree Garrison",
		.photoURL = "",
		.city = "Manchester",
		.course = "Computer Scientist",
		.skill = "Data Analysis, Internet of Things, Cloud Computing",
		.exp = "Software Analyst","Security Consultant"
	},
	{
		.email = "robert.kenzigton@gmail.com",
		.name = "Robert Kenzigton",
		.photoURL = "",
		.city = "Sacramento",
		.course = "Management",
		.skill = "Team Leadership, Schedule Management",
		.exp = "Taco Bells","Bank Manager"
	},
	{
		.email = "tom.hogan@gmail.com",
		.name = "Tom Hogan",
		.photoURL = "",
		.city = "Albuquerque",
		.course = "Design",
		.skill = "3D Modeling, UX Design, UI Design",
		.exp = "Freelancer","Inter UX Designer"
	},
	{
		.email = "robson.faker@yahoo.com",
		.name = "Robson Faker",
		.photoURL = "",
		.city = "Sacramento",
		.course = "Computer Scientist",
		.skill = "Mobile Development, Software Engineering, Cloud Computing",
		.exp = "Freelancer","iOS Developer"
	},
};


// {
// 		.email = "",
// 		.name = "",
// 		.photoURL = "",
// 		.city = "",
// 		.course = "",
// 		.skill = "",
// 		.exp = ""
// 	}

