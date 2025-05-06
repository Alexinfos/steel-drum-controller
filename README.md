# Steel drum controller

> Alexis Brandner et Camille Raynaud
> 
> Enseirb-Matmeca - I2 - 2024/2025
> 
> IT236 - Projet Makers

Code pour ESP32 permettant de piloter des solénoides jouant de la musique à partir d'une application android.

## Liens utiles
- [Présentation du projet](https://www.eirlab.net/2025/02/27/metal-drum-player/)
- [Code du contrôleur](https://github.com/Alexinfos/steel-drum-controller)

## Informations

Communication Bluetooth reprise du code d'exemple [ESP-IDF GATT SERVER SPP Example](https://github.com/espressif/esp-idf/tree/master/examples/bluetooth/bluedroid/ble/ble_spp_server)

Partie contrôle des solénoides / interprétation des commandes envoyées en Bluetooth implémentée dans [steel_drum_ctrl.c](main/steel_drum_ctrl.c)

## Comment utiliser

Avant de configurer et de compiler le projet, définir la bonne plateforme cible :

```bash
idf.py set-target <chip_name>
```

### Compilation et Flash

Lancer `idf.py -p PORT flash monitor` pour compiler, flasher et observer les logs du projet.

(Pour quitter le terminal série, taper ``Ctrl-]``.)

Voir le [Guide de Démarrage](https://idf.espressif.com/) pour les étapes complètes de configration et l'usage d'ESP-IDF pour compiler des projets.
