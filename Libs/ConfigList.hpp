
// Please, only use Config lookups with these. TODO: find something that is strongly-typed and constexpr, to enforce it
namespace Configs
{
	constexpr const char* const ResolutionX         = "render_x";
	constexpr const char* const ResolutionY         = "render_y";
	constexpr const char* const FrameRateCap        = "maxfps";
	constexpr const char* const RenderWindowStyle   = "renderwindowstyle";
	constexpr const char* const VSync               = "vsync";
}