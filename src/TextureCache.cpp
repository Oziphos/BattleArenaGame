#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <memory>
#include <string>

class TextureCache
{
public:
    // Méthode pour obtenir une instance unique du cache
    static TextureCache &getInstance()
    {
        static TextureCache instance;
        return instance;
    }

    // Récupère une texture. Si elle n'existe pas dans le cache, elle est chargée.
    std::shared_ptr<sf::Texture> getTexture(const std::string &filepath)
    {
        auto it = textures.find(filepath);
        if (it != textures.end())
        {
            return it->second; // Texture déjà chargée
        }

        // Charger et ajouter la texture au cache
        auto texture = std::make_shared<sf::Texture>();
        if (!texture->loadFromFile(filepath))
        {
            throw std::runtime_error("Erreur: Impossible de charger l'image " + filepath);
        }
        textures[filepath] = texture;
        return texture;
    }

private:
    // Constructeur privé pour garantir le singleton
    TextureCache() = default;
    ~TextureCache() = default;

    // Empêcher la copie et l'affectation
    TextureCache(const TextureCache &) = delete;
    TextureCache &operator=(const TextureCache &) = delete;

    // Map des textures
    std::unordered_map<std::string, std::shared_ptr<sf::Texture>> textures;
};
