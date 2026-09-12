#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Uses pins 20 and 21 for SCL and SDA communication


// Screen dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C address for the display
#define OLED_ADDR 0x3C

// Create SSD1306 display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Cube size variable
float size = 15; // Adjust this to change the cube's size

// Cube vertices (relative to size)
float vertices[8][3];

// Edges connecting vertices
int edges[12][2] = {
  {0, 1}, {1, 2}, {2, 3}, {3, 0},
  {4, 5}, {5, 6}, {6, 7}, {7, 4},
  {0, 4}, {1, 5}, {2, 6}, {3, 7}
};

// Rotation angles
float angleX = 0, angleY = 0;

// Function to scale and initialize vertices
void updateVertices(float size) {
  vertices[0][0] = -size; vertices[0][1] = -size; vertices[0][2] = -size;
  vertices[1][0] =  size; vertices[1][1] = -size; vertices[1][2] = -size;
  vertices[2][0] =  size; vertices[2][1] =  size; vertices[2][2] = -size;
  vertices[3][0] = -size; vertices[3][1] =  size; vertices[3][2] = -size;
  vertices[4][0] = -size; vertices[4][1] = -size; vertices[4][2] =  size;
  vertices[5][0] =  size; vertices[5][1] = -size; vertices[5][2] =  size;
  vertices[6][0] =  size; vertices[6][1] =  size; vertices[6][2] =  size;
  vertices[7][0] = -size; vertices[7][1] =  size; vertices[7][2] =  size;
}

// Function to project 3D points to 2D
void project(float x, float y, float z, int &px, int &py) {
  float distance = 50; // Perspective projection distance
  float scale = 40;
  px = (int)(SCREEN_WIDTH / 2 + (x * scale) / (z + distance));
  py = (int)(SCREEN_HEIGHT / 2 - (y * scale) / (z + distance));
}

// Function to rotate vertices
void rotate(float &x, float &y, float &z, float angleX, float angleY) {
  // Rotate around X-axis
  float newY = y * cos(angleX) - z * sin(angleX);
  float newZ = y * sin(angleX) + z * cos(angleX);
  y = newY;
  z = newZ;

  // Rotate around Y-axis
  float newX = x * cos(angleY) + z * sin(angleY);
  z = -x * sin(angleY) + z * cos(angleY);
  x = newX;
}

void setup() {
  // Initialize the display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }
  display.clearDisplay();

  // Initialize vertices
  updateVertices(size);
}

void loop() {
  display.clearDisplay();

  // Transform and draw the cube
  int projected[8][2];
  for (int i = 0; i < 8; i++) {
    float x = vertices[i][0], y = vertices[i][1], z = vertices[i][2];
    rotate(x, y, z, angleX, angleY);
    project(x, y, z, projected[i][0], projected[i][1]);
  }

  // Draw edges
  for (int i = 0; i < 12; i++) {
    int x1 = projected[edges[i][0]][0];
    int y1 = projected[edges[i][0]][1];
    int x2 = projected[edges[i][1]][0];
    int y2 = projected[edges[i][1]][1];
    display.drawLine(x1, y1, x2, y2, SSD1306_WHITE);
  }

  display.display();

  // Increment angles for rotation
  angleX += 0.05;
  angleY += 0.03;
  delay(30);
}