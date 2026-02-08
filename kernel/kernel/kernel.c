#include <flanterm/backends/fb.h>
#include <flanterm/flanterm.h>
#include <kernel/system.h>
#include <kernel/tty.h>
#include <limine.h>
#include <stdint.h>

// clang-format off

// Set the base revision to 3, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.

__attribute__((used, section(".limine_requests")))
static volatile uint64_t limine_base_revision[] = LIMINE_BASE_REVISION(4);

// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent, _and_ they should be accessed at least
// once or marked as used with the "used" attribute as done here.

__attribute__((used, section(".limine_requests")))
static volatile struct limine_framebuffer_request framebuffer_request = {
    .id = LIMINE_FRAMEBUFFER_REQUEST_ID,
    .revision = 0
};

// Finally, define the start and end markers for the Limine requests.
// These can also be moved anywhere, to any .c file, as seen fit.

__attribute__((used, section(".limine_requests_start")))
static volatile uint64_t limine_requests_start_maker[] = LIMINE_REQUESTS_START_MARKER;

__attribute__((used, section(".limine_requests_end")))
static volatile uint64_t limine_requests_end_marker[] = LIMINE_REQUESTS_END_MARKER;

// clang-format on

void kmain(void)
{
    // Ensure the bootloader actually understands our base revision (see spec).
    if (LIMINE_BASE_REVISION_SUPPORTED(limine_base_revision) == false) {
        hcf();
    }

    // Ensure we got a framebuffer.
    if (framebuffer_request.response == NULL ||
        framebuffer_request.response->framebuffer_count < 1) {
        hcf();
    }

    // Fetch the first framebuffer.
    struct limine_framebuffer *fb =
        framebuffer_request.response->framebuffers[0];
    system_setup();

    struct flanterm_context *ft_ctx = flanterm_fb_init(
        NULL, NULL,                                    //
        fb->address, fb->width, fb->height, fb->pitch, //
        fb->red_mask_size, fb->red_mask_shift,         //
        fb->green_mask_size, fb->green_mask_shift,     //
        fb->blue_mask_size, fb->blue_mask_shift,       //
        NULL,                                          //
        NULL, NULL,                                    //
        NULL, NULL,                                    //
        NULL, NULL,                                    //
        NULL, 0, 0, 1,                                 //
        0, 0,                                          //
        0                                              //
                                                       //
    );

    terminal_initialize(ft_ctx);

    hcf();
}
