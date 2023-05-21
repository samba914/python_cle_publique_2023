#include <pybind11/pybind11.h>
#include "./micro-ecc/uECC.h"

char version[]="1.0";

char const* getVersion() {
	return version;
}

class Cle
{
    private:
        char *  publicKey;
        char *  privateKey;
    public:
        Cle() {}
        ~Cle() {}

        void initialize(char *  priv) : {
            privateKey = priv;
            char * a;
            hexStringToBin(a, privateKey);
            char * b;
            calculatePublicKey(&a, &b);
        }

        char *  getPrivateKey() const {
	       return privateKey;
       	}

        char *  getPublicKey() const {
	       return publicKey;
       	}
        void hexStringToBin(unsigned char *out,const char * hexPrivate) {
            for (int i=0; i<32; i++){
            out[i] = hexchr2bin(hexPrivate[2*i])<<4 | hexchr2bin(hexPrivate[2*i+1]);
        }
}

        void calculatePublicKey(const char  *privateKey, char *publicKey) { 
            const struct uECC_Curve_t * curve = uECC_secp256k1(); 
            uECC_make_key(privateKey, publicKey, curve); 
        }

    
};
 
namespace py = pybind11;


PYBIND11_MODULE(cle_component,greetings)
{
  greetings.doc() = "greeting_object 1.0";
  greetings.def("getVersion", &getVersion, "a function returning the version");
  
   // bindings to Voiture class
    py::class_<Cle>(greetings, "Cle", py::dynamic_attr())
        .def(py::init<const std::string &, int>())
        .def("initialize", &Cle::initialize)
        .def("getPrivateKey", &Cle::getPrivateKey)
        .def("getPublicKey", &Cle::getPublicKey)
}

int main() { 
   // std::string a = "b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0"; 
    Cle c = new Cle(); 
    c.initialize("4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0")
    uint8_t publicKey[64]; privateToPublic(privateKey, publicKey); 
    // Imprimer la clé publique 
    for(int i=0; i<64; i++) { 
        printf("%02X", publicKey[i]); 
    } 
    return 0; 
}
        
