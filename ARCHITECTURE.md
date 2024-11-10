# Architecture

Application - Singleton

## Classes

### monitor (struct)

    - resolutions
    - refresh rates
    - work area

### scene 

- entities
- lights 

### Managers 

- Instances of all managers 
    - Inherit from singletons

    1. DisplayManager
        - set display
        - get displays
        - set display mode
        - get display mode
    
    2. ResourceManager
        - textures
        - shaders
        - models
        - get texture
        - get shader
        - get model

    3. InputManager
        - bind action (string action, callback)
        - bind key (string action, key)
        - listen for key press/release, mouse press/release

    4. SceneManager
        - store scenes
        - add scene
        - switch context
        - update (dt)
        - actors (entities)

    5. AudioManager

    6. PhysicsManager
        - mathematical representation
        - handles
        - scene components can track handle
        - collision event callback
            - trigger any event         

    7. RenderManager (passed scene per frame - query lights, objects)
        - Enable/Disable debug mode 
        - Add shader to render manager
            - returns handle 
            - render manager knows which shader to load based on handle
        - Add texture to render manager
            - returns handle 
            - render manager knows which texture to load based on handle
        - Sort, filter list of objects
            - Batch by shader
        - Set resolution

    8. UI Manager 
        - load/save layout
            - textures
            - types (button, dropdown, etc)

## Plan

*Window*:

- 