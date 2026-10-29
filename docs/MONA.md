# Mona: optional monitor direction

Mona is the chosen name for a future BASE1-compatible monitor or launcher.
It is separate from STR8N-F, and no Mona binary is included in 0.3.0.

STR8N-F stays the frozen 4096-byte bootstrap/recovery foundation. Mona may
show richer board/service status, offer application and subsystem menus,
hand over to an application, or deliberately return to recovery. Missing
optional hardware must be reported as unavailable. Mona owns its own name,
version and generation; these do not change F's identity or journal sequence.

MON A and MON B can provide different personalities. The current A/B boot
path requires the existing monitor image header, CRC and PR05 contract;
the labels do not make an arbitrary opaque image monitor-compatible.
Ordinary opaque images boot through a configured bank entry. The retained
g0034 monitor's [compatibility review](MON_AB_COMPATIBILITY_REVIEW.md) found it
incompatible unchanged. A new common Mona core instead passed a scoped 2512
trial. [Generation 2's RTCC adapter](MON_AB_RTCC_ADAPTER.md) passed its RAM trial
on 2512; g2 A/B ROM startup remains untested. A and B stay identical for now at
the owner's request.

Trees such as Applications / Hardware / Maintenance belong in Mona or another
optional image. LED, buzzer, SPI workspace/message services and additional
service discovery remain proposed extensions, not additions to the 0.3.0
F ABI. Implementations must be qualified separately.
