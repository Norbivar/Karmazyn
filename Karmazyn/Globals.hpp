#pragma once

namespace Karmazyn
{
	namespace Utility
	{
		namespace Container
		{
			// TODO: rework these, as they are pretty much suboptimal, but "meh, whatever" right now
			template< typename ForwardIt >
			ForwardIt getRandomElement(ForwardIt begin, ForwardIt end)
			{
				if (begin == end)
					return end;

				const auto size = std::distance(begin, end);

				boost::random::uniform_int_distribution<> randomStep(0, static_cast<int>(size));
				boost::random::mt19937 rng;
				rng.seed(static_cast<uint32_t>(std::time(0)));

				std::advance(begin, randomStep(rng));
				return begin;
			}
			template< typename Container, typename Iterator = Container::const_iterator>
			Iterator getRandomElement(const Container& container)
			{
				const auto size = container.size();
				if (size == 0)
					return container.end();

				boost::random::uniform_int_distribution<> randomStep(0, static_cast<int>(size - 1));

				boost::random::mt19937 rng;
				rng.seed(static_cast<uint32_t>(std::time(0)));
				const auto randNumber = randomStep(rng);

				Iterator it = container.begin();
				std::advance(it, randNumber);
				return it;
			}
		}
		namespace Geometry
		{
			// Returns the corresponding isometric coordinates for cartesian (standard 2D) input coordinates.
			// The argument is a coordinate pair of some number type, with strict X-Y order.
			// The returned value is of the same type as the argument with the same order of coordinates.
			template<typename BaseNumber>
			std::pair<BaseNumber, BaseNumber> cartesianToIsometric(const std::pair<BaseNumber, BaseNumber>& from)
			{
				auto isometricCoords = std::make_pair<BaseNumber, BaseNumber>(
					(from.first - from.second) / 1.5, 
					(from.first / 3.0) + (from.second / 1.5)
				);
				return isometricCoords;
			}

			// Cartesian coordinate.
			class Coordinate2D
			{
			public:
				Coordinate2D(uint64_t x, uint64_t y) : coords{ x, y } { }
				auto getAsIsometric() { return cartesianToIsometric(coords); }
				auto getAsCartesian() { return coords; }

			private:
				std::pair<uint64_t, uint64_t> coords;
			};
		}
	}
	namespace Constants
	{
		constexpr const char* const BuildVersion = "v0.02";
	}
	namespace Settings
	{
		namespace GUI
		{
			const std::string AssetsRootPath = "./data/gui";
			// This seems to fix my problems of "loading-while-rendering" buggy, so I'll rather do this.
			constexpr std::array<const char*, 2> LayoutsToLoad =
			{
				"LoadingGUI.layout",
				"MainMenuGUI.layout",
			};
			constexpr std::array<const char*, 2> LoadingScreenTipps = 
			{
				"TODO: these tipps will need to be updated, once there is something to do, as they are pretty much just placeholders, showing the overall picture of the loading screen.",
				"Lorem ipsum doloret sit amet, menj�nk d�gozni."
			};
			constexpr const char* const SchemeName = "karmazyn.scheme";
		}
	}
}
