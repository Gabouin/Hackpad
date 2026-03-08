# Gab's Hackpad — QMK Firmware

Firmware QMK en C pour le hackpad RP2040.

## Structure des fichiers

```
gabs_hackpad/
├── info.json              ← Définition hardware (pins, USB, encodeur, RGB)
├── config.h               ← Constantes (I2C, OLED, RGB, debounce...)
├── rules.mk               ← Features QMK activées
├── gabs_hackpad.h         ← Macro LAYOUT()
├── oled_display.c/.h      ← Rendu écran OLED
└── keymaps/
    └── default/
        └── keymap.c       ← Keymap + encodeur + layer callbacks
```

---

## Keymap par défaut (Layer 0 — SPOTIFY)

```
┌───────────┬───────────┬───────────┐
│    SW1    │    SW2    │    SW3    │
│  ▶/⏸ Play │  ⏮ Prev  │  ⏭ Next  │
├───────────┼───────────┼───────────┤
│    SW4    │    SW5    │    SW6    │
│  ⏹ Stop  │ 🔀 Shuffle│  ❤ Like  │
└───────────┴───────────┴───────────┘
  Encoder ↻ = Vol+    Encoder ↺ = Vol-    Encoder BTN = Mute
```

### Layer 1 — MACRO (à déclencher via combo)
| SW | Action |
|---|---|
| SW1 | Ctrl+C |
| SW2 | Ctrl+V |
| SW3 | Ctrl+Z |
| SW4 | Ctrl+S |
| SW5 | Ctrl+A |
| SW6 | Ctrl+F4 |

### Layer 2 — RGB
Contrôle direct des LEDs (toggle, mode, hue, sat, val).

---

## Comment compiler

### 1. Installer QMK

```bash
python3 -m pip install qmk
qmk setup
```

### 2. Placer le keyboard dans QMK

```bash
# Copie le dossier gabs_hackpad/ dans :
cp -r gabs_hackpad/ ~/qmk_firmware/keyboards/gabs_hackpad
```

### 3. Compiler

```bash
qmk compile -kb gabs_hackpad -km default
```

Le fichier `.uf2` sera généré dans `~/qmk_firmware/.build/` :
```
gabs_hackpad_default.uf2
```

### 4. Flasher sur le RP2040

1. Maintiens **BOOTSEL** sur le PCB en branchant le câble USB
2. Un lecteur `RPI-RP2` apparaît sur ton PC
3. Glisse le fichier `.uf2` dedans
4. Le hackpad redémarre automatiquement ✓

---

## Pin mapping (d'après schématique KiCad)

| Signal | Pin RP2040 |
|---|---|
| SW1 | GP0 |
| SW2 | GP1 |
| SW3 | GP2 |
| SW4 | GP3 |
| SW5 | GP4 |
| SW6 | GP5 |
| ENC_A | GP6 |
| ENC_B | GP7 |
| ENC_BTN | GP8 |
| OLED SDA | GP14 |
| OLED SCL | GP15 |
| LED DATA | GP16 |

> ⚠️ Vérifie ces pins avec ton schéma KiCad et ajuste `info.json` / `config.h` si besoin.

---

## OLED — affichage

L'écran affiche :
- Ligne 1 : `Gab's Hackpad`
- Ligne 2 : `Layer: SPOTIFY` (change selon le layer actif)
- S'éteint automatiquement après 30s d'inactivité

Pour ajouter ton logo : génère un bitmap 128×32 via  
https://joric.github.io/qle/ et colle les bytes dans `oled_display.c`.

---

## RGB — comportement par layer

| Layer | Couleur LEDs |
|---|---|
| SPOTIFY | 🟢 Vert (Spotify) |
| MACRO | 🔵 Bleu |
| RGB | 🔴 Rouge |

La touche SW6 (Like) fait flasher les LEDs en rouge/rose lors de l'appui.
