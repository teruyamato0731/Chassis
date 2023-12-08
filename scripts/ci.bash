# export PLATFORMIO_BUILD_CACHE_DIR="/workspaces/Chassis/.pio/cache"

# pio ci -l . -b nucleo_f446re -O "framework = mbed" examples/Mbed/4WDS
pio ci -l . -c snippets/platformio.ini examples/Mbed/Omni3
