#ifndef MENUHANDLER_H
#define MENUHANDLER_H
#include <cybermed/cybViscosity.h>
#include <cybermed/cybHaptics.h>
#include <cybermed/cybOpenHPhantom.h>
#include <cybermed/cybCore.h>
#include <cybermed/cybViewMono.h>
#include <cybermed/cybMouse.h>
#include <cybermed/cybInteratorFactory.h>

/* These macros will simplify haptic property modifications. */
#define MODIFY_HAPTIC_PROPERTY(modifier) {\
	double new_value = data[active] + modifier;\
	if (new_value > 1.0) new_value = 1.0;\
	if (new_value < 0.0) new_value = 0.0;\
	data[active] = new_value;\
}

#define MODIFY_ALL_HAPTIC_PROPERTIES(x) {\
	double new_value;\
	new_value = ((x) > (1.0)) ? (1.0) : (((x) < (0.0)) ? (0.0) : (x));\
	cybCore->setMaterialPropertyValue(0, STIFFNESS, new_value);\
	cybCore->setMaterialPropertyValue(0, DAMPING, new_value);\
	cybCore->setMaterialPropertyValue(0, STATIC_FRICTION, new_value);\
	cybCore->setMaterialPropertyValue(0, DYNAMIC_FRICTION, new_value);\
	cybCore->setMaterialPropertyValue(0, POPTHROUGH, new_value);\
}

class MenuHandler : public CybMouse
{

public: 
	static bool change;
	static CybMenu* moduloVisualizacao;
    static bool wasCreated;
	static CybParameters* cybCore;
	static int active;//layer selecionada
	static double data[5];

	/** Constructor*/
	MenuHandler();


	/** Get the singleton instance of SitegMouse*/
	static CybMouse* getUniqueInstance(); 

	/**	Creates the interactive menu.
	@param void
	@return void
	*/

	void createMenu();

	static void menuVisualizacao();
	
	static void MainMenu(int op);

	static void KeyboardFunc(unsigned char key, int x, int y);


	
};
#endif
