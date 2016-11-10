[33mcommit 0d8c6fca9f03e3c44b8848c25d7e2ab2b866125c[m
Author: Nicco Jacinto <nix_jacinto25@hotmail.com>
Date:   Wed Nov 9 02:35:11 2016 -0500

    Texture Tests
    
    +DevIL Library
    +Tests on image loading with DevIL

[33mcommit a6f328fc5cc8b7fa3c695231ce48631a81c08f56[m
Merge: 2bca8f3 a0cec91
Author: Nicco Jacinto <nix_jacinto25@hotmail.com>
Date:   Tue Nov 8 21:29:25 2016 -0500

    Merge pull request #7 from kyatohon/Camera
    
    Added Camera with basic translation and rotation.

[33mcommit a0cec91e6a3fcd39bdb0f6dc170e0047f87aaa5d[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Tue Nov 8 21:19:09 2016 -0500

    Added Camera with basic translation and rotation.
    It works, but the current version has problems due to lack of delta time
    and problem with the frustum/geometry. I assure you it works hella great
    on my other project.
    
    Also added GLFW resize handling (it simply calls GlViewport).
    Added methods for getting Mouse Position and Window Screen Size.

[33mcommit 2bca8f332668730710bcf3ad345672457a632e67[m
Merge: 3bcc2cc 7e99bb6
Author: Cat Hoang <adamhoang@live.com>
Date:   Mon Nov 7 22:31:49 2016 -0500

    Merge pull request #6 from kyatohon/BasicShaders
    
    Basic shaders

[33mcommit 7e99bb6820a86f4c6e572d39c72603f682d1ed3b[m
Author: Nicco Jacinto <nix_jacinto25@hotmail.com>
Date:   Mon Nov 7 21:31:00 2016 -0500

    Added glew for shader compilation
    
    As title

[33mcommit 158a8d34d804e2872cb765f5d7da58bc894d86e8[m
Author: Nicco Jacinto <nix_jacinto25@hotmail.com>
Date:   Mon Nov 7 20:18:59 2016 -0500

    Quick Fix
    
    Forgot to comment something out.

[33mcommit 1f261ce7b9adb3df49c511afc63e0c401bd2f72e[m
Author: Nicco Jacinto <nix_jacinto25@hotmail.com>
Date:   Mon Nov 7 20:16:39 2016 -0500

    Shader Loading Tests
    
    Testing

[33mcommit 3bcc2ccc01af01684352b33f149448d01f3e8027[m
Merge: db1247a 6973e3f
Author: Nicco Jacinto <nix_jacinto25@hotmail.com>
Date:   Mon Nov 7 15:48:10 2016 -0500

    Merge pull request #5 from kyatohon/OpenGLRenderer
    
    Switch from Vulkan -> OpenGL.

[33mcommit 6973e3f7a09cf5cc413a1fd68c4d8536edacc4ab[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Mon Nov 7 15:41:25 2016 -0500

    Deleted Vulkan related classes.
    Added Abstract and OpenGL renderer. It's still in its beginning stage.

[33mcommit 604c427d03f91ef14c9a2b78b0fc476cbeb8d83f[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Sun Nov 6 16:45:05 2016 -0500

    Upon creating the swapchain, I realized I lacked the knowledge to continue
    forwards with Vulkan.

[33mcommit 841acde9628a6e8cddc3ce9a91e4a80767b70b25[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Sat Nov 5 18:30:05 2016 -0400

    Fixed exception on Logical Device Creation.
    (It may be because driver or API is outdated, but it fixed when I added
    deprecated fields to the createInfo..)
    Created a Surface.
    Added device extension: Swapchain.

[33mcommit 2c63384b69516d34ab9a1d571b6355bd95ec8dd2[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Sat Nov 5 03:00:51 2016 -0400

    Debugging: Added validation layers.
    Also added extensions.
    Currently, the layers are finding an issue with logical device creation.

[33mcommit 1896f8ba10de2e720df0b93d3afa6349599c04f5[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Fri Nov 4 19:40:37 2016 -0400

    Added VCommander.
    Completed Logical Device, & Command Pool.
    Working on Command Buffers.

[33mcommit d660d6603716f1d7efc548b53d06823317553232[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Fri Nov 4 13:58:09 2016 -0400

    Deleted Old Failed Code.
    Added VHelper, contains helper macros for now.
    Improved Debugging formatting and consistency.
    Created VInitializer - responsible for creating Vulkan instance, logical
    device and selecting physical device.

[33mcommit ef01f0121aaa6b6d787099f5ea2175b52a07eb75[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Thu Nov 3 22:21:04 2016 -0400

    Starting VRenderer over again.
    Using the spec.
    Created VInstance and Selected PDevice.
    Currently on Logical Device Creation.

[33mcommit f619e3f7493db4f0609dc2a387fc3d81557a6665[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Sat Oct 29 18:15:06 2016 -0400

    Bug: RenderPass is invalid.
    Currently at the end of 'Command buffers'.

[33mcommit 7af7f4ba05f3683cdd74d9943372efa2e92c3e56[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Sat Oct 29 17:23:59 2016 -0400

    Added Graphics Pipeline.
    We're almost at the drawing stage.
    There are still problems with the swap chain on certain computers :(.

[33mcommit d8d962eff2d6f1289a7765f513a46aa0ced47bfa[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Fri Oct 28 15:33:25 2016 -0400

    Added VInitializer. It handles the creation of vulkan instance, surface,
    physical and logical device, present and graphics queue.
    Added shaders compilation script to repo. It may need to be changed to fit
    your own directory.

[33mcommit c6afa374d756db591859b1533e6a3c0200e50a6f[m
Author: Nicco Jacinto <nix_jacinto25@hotmail.com>
Date:   Wed Oct 26 02:16:18 2016 -0400

    Just in Time!
    
    Added a timer class
    TODO: add an accumulator for fixed updates

[33mcommit db1247a38f4a84c419ce308c36b8b5463a31070e[m
Merge: 7358770 023fe69
Author: Houshikan Yokeswaran <hau5tastic@gmail.com>
Date:   Tue Oct 25 19:50:33 2016 -0400

    Merge pull request #3 from kyatohon/architectureImprovement
    
    Improved architecture.

[33mcommit 023fe69ca1d4a3fccc712aacfd8a7b6db9b8dfcf[m
Merge: 8b8b5e4 7358770
Author: Cat Hoang <adamhoang@live.com>
Date:   Tue Oct 25 19:46:35 2016 -0400

    Merge branch 'master' into architectureImprovement

[33mcommit 7358770b3183a2ec464fdca0ee30294d0d08f179[m
Merge: 093d0d7 6b3e440
Author: Cat Hoang <adamhoang@live.com>
Date:   Tue Oct 25 19:40:45 2016 -0400

    Merge pull request #2 from kyatohon/Vulkan-Renderer
    
    Vulkan renderer

[33mcommit 6b3e44058d30f6da3f219446196d8ab5df45d787[m
Author: Houshikan Yokeswaran <hau5tastic@gmail.com>
Date:   Tue Oct 25 19:37:29 2016 -0400

    Approve or Die
    
    Vulkan Renderer Update
    
    - setup the debug callback
    - selecting physical device
    - creating logical device
    - creating swap chain
    - creating imageviews

[33mcommit fcd4612f11fd54c035511b18ed246f3b0df694b1[m
Author: Houshikan Yokeswaran <hau5tastic@gmail.com>
Date:   Tue Oct 25 19:18:12 2016 -0400

    Revert "Vulkan Renderer Update"
    
    This reverts commit 0b6a11538c7d95c6f3f343841a1b5a09475174aa.

[33mcommit 8b8b5e48981ca2db05e39bce29c4ab1ed5ab393c[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Tue Oct 25 19:16:49 2016 -0400

    Improved architecture.
    -Scene is now abstract; TestScene is the concrete implementation used in
    TestBed
    -Scene uses Singleton access instead of using parameters now.
    -Added half-finished Input Manager.

[33mcommit 0b6a11538c7d95c6f3f343841a1b5a09475174aa[m
Author: Houshikan Yokeswaran <hau5tastic@gmail.com>
Date:   Tue Oct 25 19:16:27 2016 -0400

    Vulkan Renderer Update
    
    - setup the debug callback
    - selecting physical device
    - creating logical device
    - creating swap chain
    - creating imageviews

[33mcommit 093d0d73727b37f7282438670f538db34ff86d61[m
Merge: cc0b38c b25dc8b
Author: Houshikan Yokeswaran <hau5tastic@gmail.com>
Date:   Tue Oct 25 16:02:56 2016 -0400

    Merge pull request #1 from kyatohon/architectureImprovement
    
    Architecture improvement

[33mcommit b25dc8b7a91bcc5d19eec4873c78d72b36992c83[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Tue Oct 25 15:58:36 2016 -0400

    Cleaned up code slightly.
    Added more documentation.

[33mcommit 2a4b137bdf2b4fd7a3b22bde103c0f160420e782[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Sat Oct 22 21:00:39 2016 -0400

    Somehow got Validation Layers on, but there are too many callbacks.
    Someone help me please...

[33mcommit 5f05d7114284b79a3f3aaea39a2b6a6c96a29edf[m
Author: Cat Hoang <adamhoang@live.com>
Date:   Sat Oct 22 19:39:36 2016 -0400

    Vulkan Integration Part 1:
    -Added CreateInstance
    -Stopped before Validation Layers

[33mcommi