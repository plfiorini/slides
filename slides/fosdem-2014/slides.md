title: Me

---

title: What is this stuff?

Maui:

- Convenient way to distribute the desktop
- GNU/Linux stack, Qt, Hawaii
- Atomic, safe updates and upgrades (OSTree)
- Download only what's changed, zlib compressed
- Bundles instead of packages
- Focused on Qt and desktop needs

Hawaii:

- Low footprint Wayland and QtQuick based desktop
- Modular, less dependencies
- Adapt to different devices
- Customizable layouts
- Easier styling

---

title: Updates often gets in your way
class: nobackground fill
content_class: flexbox vcenter

This is during yum update: the system is in an inconsistent state

![During an upgrade](during-upgrade.png)

---

title: Updates

- Step 1: fetch updates and apply them atomically
- Step 2: reboot into the updated system

Advantages:

- **If something fails at step 1 you won't reboot into a broken system**
- Updates are atomic, only one reboot
- No need for rescue partitions or BTRFS snapshots
- Ability to reboot into older version in case of regressions
- Same workflow for **upgrades to the new OS release**

---

title: mauibuild
subtitle: What it does now

- Base system built from [Yocto](https://www.yoctoproject.org/)
- Builds git repositories from core up to Hawaii, plus a few apps
- Can build continuosly
- Outputs different trees: runtime, runtime-debug, devel, devel-debug
- Targets bare metal
- Creates live images

---

title: mauibuild
subtitle: Ideas for the future

- Pick a more complete base system (e.g. Mer, Fedora) and only build Qt and Hawaii
- Focus on continuous integration, smoke tests and QA
- Only target virtualized environments
- No security updates

---

title: Hawaii: philosophy
class: big

- Collaborate with upstream
- Reuse other libraries when possible
- Avoid unnecessary or bloated stuff
- Only support Wayland
- Adapt to diffent form factors
- Modular desktop with components
- Easy and reliable API for styles

---

title: Few dependencies
class: fill
content_class: flexbox vcenter

![Too much stuff](too_much_stuff.png)

---

title: Low memory footprint
content_class: flexbox vcenter

**Consumes approximately 60:70 MB**

![Low memory footprint](memusage.png)

---

title: Features on 0.2.0

- Multiple screens support without primary and secondary outputs
- Launcher, Panel and AppChooser on multiple pages
- Background with crossfade effect
- Modal dialogs, overlays and popups
- Multiple workspaces and switcher
- Windows switcher and Exposé-like presentation
- Lock screen
- PolicyKit agent
- Notifications
- Volume control keys
- Grouped indicators and consolidated menu
- QML styles

---

title: Features for upcoming version

- Switch between different layouts
- First step towards desktop and mobile convergence
- Customizable layouts
- Loadable elements
- Replaceable components (lock screen, ...)
- More modularization
- Screen saver
- Animated wallpapers
- Workspaces overview
- Dropdown windows
- Wayland/Weston 1.4 support
- Possibly more core apps: Weather and Cinema

---

title: What's next?

- Port SDDM to Wayland
- Improved applications and task management
- Freedesktop.org Notifications 1.2
- More preference modules: keyboard, mouse, screens, ...

---

title: KDE Frameworks

- Less dependencies than before
- Code ready to be used, less duplication
- More people involved, more stable code
- Larger userbase

---

title: Styles

<pre class="prettyprint" data-lang="qml">
import QtQuick 2.0
import Hawaii.Shell.Styles.Base 1.0

OverlayStyle {
    textColor: "white"
    textShadowColor: Qt.rgba(0, 0, 0, 0.7)
    panel: Rectangle {
        border.color: Qt.rgba(0, 0, 0, 0.5)
        gradient: Gradient {
            GradientStop { position: 0.0; color: Qt.rgba(0.13, 0.13, 0.13, 0.7) }
            GradientStop { position: 0.5; color: Qt.rgba(0, 0, 0, 0.7) }
            GradientStop { position: 1.0; color: Qt.rgba(0, 0, 0, 0.7) }
        }
        radius: 6
        antialiasing: true
    }
}
</pre>

---

title: How do I get it?

- Sources: [github.com/mauios](https://github.com/mauios)
- AUR packages for Arch Linux
- Binary packages for Arch Linux (x86_64) always updated
- On going effort on Mer
- Fedora: coming soon

---

title: Convergence

Write less code, concentrate on what really changes.

---

title: What you can do to contribute

- Coding (Qt, QML, C/C++)
- UI, styles and Web design
- Graphics (icon themes and such)
- Wallpapers
- Writing documentation (HIG, wiki, manuals, ...)
- Web site (HTML and CSS)
- Help organizing a community space with forums
- Videos and marketing stuff
- Spread the word
- Donate some money
- Donate hardware, server, hosting
- Sponsor development
