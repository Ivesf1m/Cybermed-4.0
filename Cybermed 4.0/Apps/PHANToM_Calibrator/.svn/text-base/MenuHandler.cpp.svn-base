#include "MenuHandler.h"

	bool MenuHandler::change = false;
	CybMenu* MenuHandler::moduloVisualizacao;
	bool MenuHandler::wasCreated;
	CybParameters* MenuHandler::cybCore;
	int MenuHandler::active = 0;//layer selecionada
	double MenuHandler::data[5] = { 0.2, 0.2, 0.2, 0.2, 0.0 };

	/** Constructor*/
	MenuHandler::MenuHandler()
	{ 
		
	}

	/** Get the singleton instance of SitegMouse*/
	CybMouse* MenuHandler::getUniqueInstance() 	
	{
		if(!singletonInstance)
			singletonInstance = new MenuHandler();
		return singletonInstance;
	 }

	/**	Creates the interactive menu.
	@param void
	@return void
	*/

	void MenuHandler::createMenu()
	{	
			menuVisualizacao();		
			glutKeyboardFunc(KeyboardFunc);
		
	}

	void MenuHandler::menuVisualizacao() 
	{
		cybCore= CybParameters::getInstance();
		moduloVisualizacao = CybMenu::getNewMenu(MainMenu);
		wasCreated = false;
		int i;
		
		if(!wasCreated)
		{	
			moduloVisualizacao->add("Stiffness", 0);
			moduloVisualizacao->add("Damping", 1);
			moduloVisualizacao->add("Static Friction", 2);
			moduloVisualizacao->add("Dynamic Friction", 3);
			moduloVisualizacao->add("Pop Through", 4);

			wasCreated = true;
		}
		moduloVisualizacao->createMenu();
	}

	
	void MenuHandler::MainMenu(int op)
	{
		switch (op) {
			case 0: 
			case 1:
			case 2: 
			case 3:
			case 4: active = op; break;
			default: break;
		}
	}

	void MenuHandler::KeyboardFunc(unsigned char key, int x, int y)
	{
		CybParameters *cybCore = CybParameters::getInstance();

		switch (key) {
			case '1': {
				MODIFY_HAPTIC_PROPERTY(0.05);
				cout << "+0.05" << endl;
				break;
			}
			case '2': {
				MODIFY_HAPTIC_PROPERTY(-0.05);
				cout << "-0.05" << endl;
				break;
			}
			case 'p': {
				std::cout << "\nPrinting properties."
				<< "\n Stiffness: " 
				<< cybCore->getMaterialPropertyValue(0, STIFFNESS)
				<< "\n Damping: " 
				<< cybCore->getMaterialPropertyValue(0, DAMPING)
				<< "\n Static Friction: " 
				<< cybCore->getMaterialPropertyValue(0, STATIC_FRICTION)
				<< "\n Dynamic Friction: " 
				<< cybCore->getMaterialPropertyValue(0, DYNAMIC_FRICTION)
				<< "\n Popthrough: " 
				<< cybCore->getMaterialPropertyValue(0, POPTHROUGH) 
				<< std::endl;
				break;
			}
			case 27: exit(0);
		}

		cybCore->setMaterialPropertyValue(0, STIFFNESS, data[0]); 
		cybCore->setMaterialPropertyValue(0, DAMPING, data[1]); 
		cybCore->setMaterialPropertyValue(0, STATIC_FRICTION, data[2]); 
		cybCore->setMaterialPropertyValue(0, DYNAMIC_FRICTION, data[3]); 
		cybCore->setMaterialPropertyValue(0, POPTHROUGH, data[4]);	

		cybCore->materialFaceModified = true;
		glutPostRedisplay();
	}
