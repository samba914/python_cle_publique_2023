#include <pybind11/pybind11.h>

char version[]="1.0";

char const* getVersion() {
	return version;
}

class Voiture
{
    public:
        Voiture(const std::string &nom, int volumeEssence) : nom(nom), volumeEssence(volumeEssence) {}
        ~Voiture() {}

        void roule() {
	       volumeEssence--;
       	}
        const std::string &get_nom() const {
	       return nom;
       	}
        int get_volumeEssence() const {
	       return volumeEssence;
       	}
	void remplirEssence(int &essence_) {
	       volumeEssence = volumeEssence + essence_;
       	}

    private:
        std::string nom;
        int volumeEssence;
};
 
namespace py = pybind11;


PYBIND11_MODULE(voiture_component,greetings)
{
  greetings.doc() = "greeting_object 1.0";
  greetings.def("getVersion", &getVersion, "a function returning the version");
  
   // bindings to Voiture class
    py::class_<Voiture>(greetings, "Voiture", py::dynamic_attr())
        .def(py::init<const std::string &, int>())
        .def("roule", &Voiture::roule)
        .def("get_volumeEssence", &Voiture::get_volumeEssence)
        .def("get_nom", &Voiture::get_nom)
	.def("remplirEssence", &Voiture::remplirEssence);
}
