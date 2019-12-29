#pragma once


#include <Libs/Logging>
#include <Libs/Config>
#include <Karmazyn/Globals.hpp>

#include <cstdint>
#include <chrono>
#include <memory>
#include <thread>
#include <atomic>
#include <string>
#include <set>
#include <array>
#include <vector>
#include <unordered_map>

#include <type_traits>
#include <typeinfo>

#include <boost/container/static_vector.hpp>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/asio.hpp>

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GL3Renderer.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Graphics.hpp>
