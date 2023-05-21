#include <pybind11/pybind11.h>
#include "./micro-ecc/uECC.h"

char version[]="1.0";

char const* getVersion() {
	return version;
}

class Cle
{
    private:
        std::string publicKey;
        std::string privateKey;
    public:
        Cle() {}
        ~Cle() {}

        initialize(std::string priv) : {
            privateKey = priv
            uint8_t a = hexStringToUint8(privateKey);
            uint8_t b;
            calculatePublicKey(&a, &b);
        }

        std::string getPrivateKey() const {
	       return privateKey;
       	}

        std::string getPublicKey() const {
	       return publicKey;
       	}

        void calculatePublicKey(const uint8_t *privateKey, uint8_t *publicKey) {
            const struct uECC_Curve_t * curve = uECC_secp256k1();
            uECC_make_key(privateKey, publicKey, curve);
        }

        uint8_t hexStringToUint8(const std::string& hexString) {
            std::stringstream ss(hexString);
            int value;
            ss >> intValue;

            if(intValue < 0 || intValue > 255 ){}


            return static_cast<uint8_t>(intValue);
           /* for (int i = 0; i < 32; i++) {
                uint16_t value = 0;
                ss >> std::hex >> value;
                result[i] = static_cast<uint8_t>(value);
            }

            return result;*/
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
    initialize(”4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0”)
    uint8_t publicKey[64]; privateToPublic(privateKey, publicKey);
    // Imprimer la clé publique
    for(int i=0; i<64; i++) {
        printf("%02X", publicKey[i]);
    }
    return 0;
}

