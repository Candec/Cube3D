make re

echo "ERROR MAPS"
echo "-----------------------"

echo "[TEST] - Empty map"
./cub3d maps/empty_map.cub
echo "\n"
echo "[TEST] - Invalid character"
./cub3d maps/invalid_chr.cub
echo "\n"
echo "[TEST] - Invalid format"
./cub3d maps/invalid_format.ber
echo "\n"
echo "[TEST] - Invalid map"
./cub3d maps/invalid_map.cub
echo "\n"
echo "[TEST] - Invalid path"
./cub3d maps/invalid_texture_path.cub
echo "\n"
echo "[TEST] - Tabs after map"
./cub3d maps/tab_by_the_right.cub
echo "\n"
echo "\n"

echo "WORKING MAPS"
echo "-----------------------"

echo "[TEST] - Extra line"
./cub3d maps/invalid_extra_line.cub
echo "[TEST] - Big map"
./cub3d maps/big_map.cub
echo "[TEST] - Small map"
./cub3d maps/small_map.cub
echo "[TEST] - Normal map"
./cub3d maps/map.cub
