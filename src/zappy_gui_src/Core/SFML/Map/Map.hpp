/*
** EPITECH PROJECT, 2022
** zappy
** File description:
** Map
*/

/// \file src/zappy_gui_src/Core/SFML/Map/Map.hpp

#ifndef MAP_HPP_
#define MAP_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <vector>
#include "Tile.hpp"
#include "Event.hpp"
#include "Entity.hpp"
#include "Animation.hpp"

#define FOOD_PATH "./assets/food.png"
#define LINEMATE_PATH "assets/linemate.png"
#define MENDIANE_PATH "assets/mendiane.png"
#define PHIRAS_PATH "assets/phiras.png"
#define DERAUMERE_PATH "assets/deraumere.png"
#define SIBUR_PATH "assets/sibur.png"
#define THYSTAME_PATH "assets/thystame.png"

#define PLAYER1_PATH "assets/player1.png"
#define PLAYER2_PATH "assets/player2.png"
#define PLAYER3_PATH "assets/player3.png"

#define EGG_PATH "assets/egg.png"

#define SOUND_SPAWN_PATH "assets/spawn.wav"
#define SOUND_DEATH_PATH "assets/death.wav"
#define SOUND_EGG_PATH "assets/egg.wav"
#define SOUND_WIN_PATH "assets/egg.wav"
#define SOUND_LOSE_PATH "assets/loose.wav"

namespace gui {
    /// \brief enum of index of sounds
    typedef enum sounds_e {
        /// \brief index of spawn sound
        SPAWN_SOUND,
        /// \brief index of death sound
        DEATH_SOUND,
        /// \brief index of egg sound
        EGG_SOUND,
        /// \brief index of win sound
        WIN_SOUND,
        /// \brief index of loose sound
        LOSE_SOUND
    } sounds_t;
    /// \brief Class for the map of the zappy. It contain all informations that will be display.
    class Map {
        public:

            /// \brief Constructor of the Map.
            Map();

            /// \brief Destructor of the Map.
            ~Map() = default;

            /// \brief Set the render window to display on.
            /// \param window The window to be set.
            inline void setWindow(std::shared_ptr<sf::RenderWindow> window) {
                _window = window;
            };

            /// \brief Set the event class to be used.
            /// \param event The event to be set.
            inline void setEvent(std::shared_ptr<Event> event) {
                _event = event;
            };

            /// \brief Set the size of the map.
            /// \param mapSize The size of the map.
            inline void setMapSize(sf::Vector2f mapSize) {
                _mapSize = mapSize;
                _updateTileVectorSize();
                _SetDefaultMapOrigin();
            };

            /// \brief Display the map on the window. Update all information of the map if necessary.
            void display();

             /// \brief Get the vector of players of the tile.
            /// \return The vector of players.
            inline const std::vector<gui::entity::Player> &getPlayers() const {
                return _players;
            };

            /// \brief add a player object to the vector
            /// \param player the player object to add
            /// \warning for the moment, the sound is played when a player join a new team,
            /// GUI need to know the UUID of the player so he'll play the sound only of a new player
            inline void addPlayer(gui::entity::Player &player) {
                std::size_t tmp = itop(sf::Vector2f(player.getPosition().first, player.getPosition().second));

                _players.emplace_back(player);
                if (tmp < _tile.size())
                    _tile[tmp]->addPlayer(player);
                for (auto &team : _teams) {
                    if (team == player.getTeamName())
                        return;
                }
                _sounds.at(SPAWN_SOUND)->play();
                _teams.emplace_back(player.getTeamName());
                _teamsColor.emplace_back(sf::Color(rand() % 255, rand() % 255, rand() % 255));
            }

            /// \brief Get the vector of players of the tile.
            /// \return The vector of players.
            inline const std::vector<gui::entity::Tile> &getTilesInfo() const {
                return _tilesInfo;
            };

            /// \brief add a tile object to the vector
            /// \param tileInfo the tile object to set
            inline void addTilesInfo(gui::entity::Tile &tileInfo) {
                _tilesInfo.emplace_back(tileInfo);
                _tile[itop(sf::Vector2f(tileInfo.getPosition().first, tileInfo.getPosition().second))]->setTileInfo(tileInfo);
            }

            /// \brief Get the vector of players of the tile.
            /// \return The vector of players.
            inline const std::vector<gui::entity::Egg> &getEggs() const {
                return _eggs;
            };

            /// \brief add a player object to the vector
            /// \param tileInfo the player object to add
            inline void addEgg(gui::entity::Egg &egg) {
                _sounds.at(EGG_SOUND)->play();
                _eggs.emplace_back(egg);
                _tile[itop(sf::Vector2f(egg.getPosition().first, egg.getPosition().second))]->addEgg(egg);
            }

            /// \brief remove entities depending on the type given
            /// \param type string representating the type of entities to remove
            void removeEntities(std::string &type);

            /// \brief get the posititon of the selected tile
            /// \return the position of the tile selected by the user
            inline const sf::Vector2f &getSelectedTilePos() const {
                if (int(_tileSelected) == -1)
                    return _noTileSelected;
                return _tile[_tileSelected].get()->getPosition();
            };

            /// \brief get the inventory selected tile
            /// \return the inventory of the tile selected by the user
            inline const std::vector<int> &getSelectedTileInventory() const {
                if (int(_tileSelected) == -1)
                    return _noTileSelectedInv;
                return _tile[_tileSelected].get()->getTileInfo().getInventory();
            };

            /// \brief get the vector of players on the selected tile
            /// \return the vector of players on the tile selected by the user
            inline const std::vector<gui::entity::Player> &getSelectedTilePlayers() const {
                if (int(_tileSelected) == -1)
                    return _noTileSelectedPlayer;
                return _tile[_tileSelected].get()->getPlayers();
            };

            /// \brief get the vector of eggs on the selected tile
            /// \return the vector of eggs on the tile selected by the user
            inline const std::vector<gui::entity::Egg> &getSelectedTileEggs() const {
                if (int(_tileSelected) == -1)
                    return _noTileSelectedEggs;
                return _tile[_tileSelected].get()->getEggs();
            };
        private:

            bool _mapCanMove(sf::Vector2f mapMove);

            /// \brief Set the defaut origin of the map on the map center.
            void _SetDefaultMapOrigin();

            /// \brief Display the actual selected and hover tile if it's different to index -1. It also display the entity one these tile, otherwise they won't be displayed.
            /// \param entityRepresentation The circle shape used to display entities.
            void _displaySelectedTile();

            /// \brief Display the actual selected and hover tile if it's different to index -1. It also display the entity one these tile, otherwise they won't be displayed.
            /// \param entityRepresentation The circle shape used to display entities.
            void _displayHoveredTile();

            /// \brief Find if the selected or hover tile must be update.
            /// \param i The actual index of the tile to find if it need to be update.
            /// \param mouse The mouse cursor position on the window.
            void _findSelectedAndHoverTiles(std::size_t &i, const sf::Vector2i &mouse);

            /// \brief Update the position of the map depending on events.
            void _updateMoveMap();

            /// \brief Transform a vector position to an index.
            /// \param pos The position to be transform.
            /// \return The corresponding index of the pos.
            inline std::size_t itop(sf::Vector2f pos) {
                return pos.y * _mapSize.x + pos.x;
            };

            /// \brief Transfom an index to a position.
            /// \param index The index to be transfom.
            /// \return The corresponding pos of the index.
            inline sf::Vector2f ptoi(std::size_t index) {
                return sf::Vector2f(index % int(_mapSize.y), index / _mapSize.y);
            };

            /// \brief Find if the tile should be displayed on the screen.
            /// \param area The global bound of the tile.
            /// \param windowSize The size of the window.
            /// \param tmp A value use to keep a previous value.
            /// \param mapSize The size of the map.
            /// \param i The index in the tile vector.
            /// \return true if it should be displayed, false otherwise.
            bool _tileMustBeDisplayed(const sf::FloatRect &area, const sf::Vector2u windowSize, std::size_t &tmp, sf::Vector2f &mapSize, std::size_t &i);

            /// \brief Update the size of the vector.
            void _updateTileVectorSize();

            /// \brief Display players that are in the tile, if there is at least one player.
            /// \param tile The tile to get information from.
            /// \param playerRepresentation The representation of a player as a green circle shape.
            void _displayPlayers(Tile &tile);

            /// \brief Display resources that are in the tile, if there is at least one resource.
            /// \param tile The tile to get information from.
            /// \param resourcesRepresentation The representation of a resource as a grey circle shape.
            void _displayResources(Tile &tile);

            /// \brief Display eggs that are in the tile, if there is at least one egg.
            /// \param tile The tile to get information from.
            /// \param eggRepresentation The representation of an egg as a yellow circle shape.
            void _displayEggs(Tile &tile);

            /// \brief initialize all the paths vector for ressources
            void _initRessourcesPaths();

            /// \brief initialize all animations for entities
            void _initAnimationEntities();

            /// \brief initialize a sound
            void _initSound(int index);

            /// \brief initialize a soundBuffer with a path
            /// \param path The path of the sound to initialize
            void _initSoundBuffer(const char *path, int index);

            /// \brief initialize all the sounds
            void _initSounds();

            /// \brief initialize all the soundsBuffer

            /// \brief find the color of a team
            /// \param teamName the team
            /// \return the color of the team
            sf::Color _findTeamColor(const std::string &teamName);

            /// \brief The window to display on.
            std::shared_ptr<sf::RenderWindow> _window;

            /// \brief The event class.
            std::shared_ptr<Event> _event;

            /// \brief The tile's vector in the map.
            std::vector<std::unique_ptr<Tile>> _tile;

            /// \brief The selected tile.
            std::size_t _tileSelected;

            /// \brief the default pos of no tile selected
            sf::Vector2f _noTileSelected;

            /// \brief the default vector of no tile selected inventory
            std::vector<int> _noTileSelectedInv;

            /// \brief the default vector of no tile selected players
            std::vector<gui::entity::Player> _noTileSelectedPlayer;

            /// \brief the default vector of no tile selected eggs
            std::vector<gui::entity::Egg> _noTileSelectedEggs;

            /// \brief The hovered tile.
            std::size_t _tileHover;

            /// \brief The vector size of the map.
            sf::Vector2f _mapSize;

            /// \brief Zoom to be applied.
            float _zoom;

            /// \brief vector of tiles info
            std::vector<gui::entity::Tile> _tilesInfo;

            /// \brief vector of players to be displayed on the tile
            std::vector<gui::entity::Player> _players;

            /// \brief vector of eggs to be displayed on the tile
            std::vector<gui::entity::Egg> _eggs;

            /// \brief vector of paths for ressources
            std::vector<std::string> _ressourcesPaths;

            /// \brief object animation for the ressources
            std::vector<Animation> _ressourcesAnim;

            /// \brief object animation for the player
            Animation _playerAnimation;

            /// \brief object animation for the player
            Animation _eggAnimation;

            /// \brief vector of all the teams
            std::vector<std::string> _teams;

            /// \brief vector of team linked to a color
            std::vector<sf::Color> _teamsColor;

            using SoundPtr = std::shared_ptr<sf::Sound>;

            /// \brief vector of all the sounds
            /// \warning the order of the sounds is
            /// SPAWN, DEATH, EGG, WIN, LOOSE
            std::vector<SoundPtr> _sounds;

            /// \brief vector of all the soundsBuffer
            /// \warning the order of the sounds is
            /// SPAWN, DEATH, EGG, WIN, LOOSE
            std::vector<sf::SoundBuffer> _soundsBuffer;
    };
} // namespace gui

#endif /* !MAP_HPP_ */
