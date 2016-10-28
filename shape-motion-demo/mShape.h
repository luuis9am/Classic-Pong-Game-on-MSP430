
struct {
  DispShape *ds;
  Vec2 velocity;
} MovShape;

struct {
  MovShapes *movShapeVec;
  int vecLen;
  Region bounds;
} MovShapes;


void msMove(MovShapes *ms);
