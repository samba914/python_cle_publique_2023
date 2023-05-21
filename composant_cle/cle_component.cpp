#include <string>
#include <pybind11/pybind11.h>
#include "./micro-ecc/uECC.h"

char version[]="1.0";

const char* getVersion() {
	return version;
}

class Cle
{
    private:
        std::string publicKey;
        std::string privateKey;
        
        unsigned char hexchr2bin(const char hex)
        {
            unsigned char result;

            if (hex >= '0' && hex <= '9') {
                result = hex - '0';
            } else if (hex >= 'A' && hex <= 'F') {
                result = hex - 'A' + 10;
            } else if (hex >= 'a' && hex <= 'f') {
                result = hex - 'a' + 10;
            } else {
                return 0;
            }
            return result;
        }

        void hexStringToBin(unsigned char *out, const char * hexPrivate) {
            for (int i=0; i<32; i++){
                out[i] = hexchr2bin(hexPrivate[2*i])<<4 | hexchr2bin(hexPrivate[2*i+1]);
            }
        }

        void calculatePublicKey(unsigned char *privateKey, unsigned char *publicKey) { 
            const struct uECC_Curve_t * curve = uECC_secp256k1();
            if (!uECC_compute_public_key(privateKey, publicKey, curve)) {
                // Handle error: computing public key failed
            }
        }

        std::string binaryToHex(const std::string& binary) const {
            std::string hex;
            hex.reserve(binary.size() * 2);
            for (unsigned char c : binary) {
                hex.push_back("0123456789ABCDEF"[c >> 4]);
                hex.push_back("0123456789ABCDEF"[c & 0xF]);
            }
            return hex;
        }

    public:
        Cle() {}
        ~Cle() {}

        void initialize(const std::string& priv) {
            privateKey = priv;
            unsigned char a[64];
            hexStringToBin(a, privateKey.c_str());
            unsigned char b[64];
            calculatePublicKey(a, b);
            publicKey = std::string((char*)b, 64);
        }

        std::string getPrivateKey() const {
	       return privateKey;
       	}

        

        std::string getPublicKey() const {
            return binaryToHex(publicKey);
        }

};

namespace py = pybind11;

PYBIND11_MODULE(cle_component,greetings)
{
  greetings.doc() = "greeting_object 1.0";
  greetings.def("getVersion", &getVersion, "a function returning the version");
  
    py::class_<Cle>(greetings, "Cle", py::dynamic_attr())
            .def(py::init<>())
        .def("initialize", &Cle::initialize)
        .def("getPrivateKey", &Cle::getPrivateKey)
        .def("getPublicKey", &Cle::getPublicKey);
}


