function setup() {

}

var tilt_dir = 5;
var tilt_angle = 90;

var pan_dir = 1;
var pan_angle = 0;

function loop() {
  tilt_angle += tilt_dir;
  /*
  if (tilt_angle <= 85 || tilt_angle >= 105) {
    tilt_dir = -tilt_dir;
  }
  */
  if (tilt_angle <= 75 || tilt_angle >= 105) {
    tilt_dir = -tilt_dir;
  }

  pan_angle += pan_dir;
  if (pan_angle <= -15 || pan_angle >= 15) {
    pan_dir = -pan_dir;
  }

  pan.write(90 + 20 * pan_dir);
  tilt.write(tilt_angle);
}
