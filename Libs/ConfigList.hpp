
// Please, only use Config lookups with these. TODO: find something that is strongly-typed and constexpr, to enforce it
// Or static analyzers/grep could find it easily, so I will not bother bloating the code with structs and such.
namespace Configs
{
	constexpr const char* const ResolutionX         = "render_x";
	constexpr const char* const ResolutionY         = "render_y";
	constexpr const char* const FrameRateCap        = "maxfps";
	constexpr const char* const RenderWindowStyle   = "renderwindowstyle";
	constexpr const char* const VSync               = "vsync";
}