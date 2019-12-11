robotino-pkg
============

Objectifs :
-----------
* Version stable et compatible catkin des paquets ros robotino
* Garder la compatibilité avec le robotino 2
* Migrer vers ROS2

Migration à ROS2 :
------------------
* Compilation (uniquement les packages déjà migrés) :

`colcon build --packages-select robotino_msgs robotino_node robotino_teleop`

Statut de la migration :

Compilation :
- [x] robotino_msgs
- [x] robotino_node  
    - [x] robotino_node
    - [x] robotino_odometry_node
    - [x] robotino_camera_node
    - [x] robotino_laserrangefinder_node

- [x] robotino_teleop
    - [x] joystick_teleop_node
    - [x] keyboard_teleop_node

- [ ] robotino_local_move
- [ ] robotino_local_planner
- [ ] robotino_description
- [ ] robotino_safety
- [ ] robotino_navigation

Tests :

- [x] robotino_msgs
- [ ] robotino_node  
    - [ ] robotino_node
    - [x] robotino_odometry_node
    - [ ] robotino_camera_node
    - [ ] robotino_laserrangefinder_node

- [ ] robotino_teleop
    - [ ] joystick_teleop_node
    - [x] keyboard_teleop_node

- [ ] robotino_local_move
- [ ] robotino_local_planner
- [ ] robotino_description
- [ ] robotino_safety
- [ ] robotino_navigation
