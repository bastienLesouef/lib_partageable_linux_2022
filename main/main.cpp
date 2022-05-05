
#include <iostream>
#include <dlfcn.h>

int main(int argc, char ** argv)
{
	// in this main we have removed the explicit 
	// link to the components.
	int valeur1=3;
	int valeur2=5;
	
	// we'll use dlopen 
	void *handle1 = nullptr;
    	void *handle2 = nullptr;
	
	handle1 = dlopen("./libComposant1.so", RTLD_LAZY);
	handle2 = dlopen("./libComposant2.so", RTLD_LAZY);
	
	// check if there is some errors during the link
	if (!handle1 || !handle2) {
        	fprintf(stderr, "%s\n", dlerror());
        	exit(EXIT_FAILURE);
    	}
	
	int (*composant1)(int, int);
    	int (*composant2)(int, int);
    	*(void **) (&composant1) = dlsym(handle1, "composant1");
    	*(void **) (&composant2) = dlsym(handle2, "composant2");
	
	valeur1 = (*composant1)(valeur1,valeur2);
    	valeur2 = (*composant2)(valeur1,valeur2);
    	std::cout << "valeur 1 :" << valeur1 << " valeur 2 :" << valeur2 << std::endl;
	
	// close the dll
    	dlclose(handle1);
    	dlclose(handle2);
    	exit(EXIT_SUCCESS);
}
