import cle_component

# Créez une instance de la classe Cle
macle = cle_component.Cle()

# Initialisez avec une clé privée
macle.initialize("4b8e29b9b0dddd58a709edba7d6df6c07ebdaf5653e325114bc5318c238f87f0")

# Récupérez la clé privée
print(macle.getPrivateKey())

# Récupérez la clé publique
print(macle.getPublicKey())