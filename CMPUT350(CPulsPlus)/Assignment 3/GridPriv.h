// list private Grid members here

// ...

int width, height; //to store the total width and height of the grid structure

std::array<std::array<Grid::Tile, height>, width> gridTiles; //an array to store the tiles by row

std::map<std::array<int, 5>, bool> used_coords; //a map to store coordinate pairs that have been sent to the isCOnnected funtion with their result, the key stores size/coordinates and the value is connected

bool isCon_calledBefore; //given the current state of the map, has isConnected been called before



