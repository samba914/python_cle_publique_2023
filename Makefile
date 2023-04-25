
all: component1 component2

component1:
	cd hello && ${MAKE}

component2:
	cd voiture && ${MAKE}

