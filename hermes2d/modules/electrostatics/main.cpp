#include "hermes2d.h"
#include "disc.h"
#include "electrostatics.h"

int main(int argc, char* argv[])
{

  /*** RECEIVE DATA ***/

  // Check the number of command line arguments.
  if(argc != 2) error("Configuration file missing.");
  // Open configuration file.
  FILE* f = fopen(argv[1], "r");
  if(f == NULL) error("Cannot open file %s.", argv[1]);
  // Mesh filename.
  char *mesh_filename = new char[200];
  if(!Get(f, mesh_filename)) error("Could not read mesh filename.");
  // Number of initial uniform mesh refinements.
  int init_ref_num;
  if(!Get(f, &init_ref_num)) error("Could not read number of initial mesh refinements.");
  // Initial polynomial degree of elements.
  int init_p;
  if(!Get(f, &init_p)) error("Could not read number of initial polynomial degree.");
  // Number of material markers.
  int n_mat_markers;
  if(!Get(f, &n_mat_markers)) error("Could not read number of material markers.");
  if(n_mat_markers <= 0) error("At least one material merker must be given.");
  // Array of material markers.
  int* mat_markers = (int*)malloc(n_mat_markers*sizeof(int));
  for (int i = 0; i < n_mat_markers; i++) {
    if(!Get(f, mat_markers + i)) error("Could not read a material marker.");
  }
  // Array of material constants (permittivities).
  double* permittivity_array = (double*)malloc(n_mat_markers*sizeof(double));
  for (int i = 0; i < n_mat_markers; i++) {
    if(!Get(f, permittivity_array + i)) error("Could not read a permittivity.");
  }
  // Array of material constants (charge densities).
  double* charge_density_array = (double*)malloc(n_mat_markers*sizeof(double));
  for (int i = 0; i < n_mat_markers; i++) {
    if(!Get(f, charge_density_array + i)) error("Could not read a charge density.");
  }
  // Number of VALUE boundary conditions.
  int n_bc_value;
  if(!Get(f, &n_bc_value)) error("Could not read number of VALUE boundary markers.");
  if(n_bc_value <= 0) error("At least one VALUE boundary marker must be given.");
  // VALUE boundary markers.
  int* bc_markers_value = (int*)malloc(n_bc_value*sizeof(int));
  for (int i = 0; i < n_bc_value; i++) {
    if(!Get(f, bc_markers_value + i)) error("Could not read a VALUE boundary marker.");
  }
  // Boundary values (electric potential).
  double* bc_values = (double*)malloc(n_bc_value*sizeof(double));
  for (int i = 0; i < n_bc_value; i++) {
    if(!Get(f, bc_values + i)) error("Could not read a boundary value.");
  }
  // Number of DERIVATIVE boundary conditions.
  int n_bc_derivative;
  if(!Get(f, &n_bc_derivative)) error("Could not read number of DERIVATIVE boundary markers.");
  // DERIVATIVE boundary markers.
  int* bc_markers_derivative = NULL;
  double* bc_derivatives = NULL;
  // Boundary derivatives.
  if(n_bc_derivative >= 1) {
    bc_markers_derivative = (int*)malloc(n_bc_derivative*sizeof(int));
    for (int i = 0; i < n_bc_derivative; i++) {
      if(!Get(f, bc_markers_derivative + i)) error("Could not read a DERIVATIVE boundary marker.");
    }
    bc_derivatives = (double*)malloc(n_bc_derivative*sizeof(double));
    for (int i = 0; i < n_bc_derivative; i++) {
      if(!Get(f, bc_derivatives + i)) error("Could not read a boundary derivative.");
    }
  }


  /*** FEED THE DATA INTO THE ELECTROSTATICS MODULE ***/

  // Initialize the Electrostatics class.
  Electrostatics E;

  // Set mesh filename.
  E.set_mesh_filename(mesh_filename);
  
  // Set number of initial uniform mesh refinements.
  E.set_initial_mesh_refinement(init_ref_num);

  // Set initial polynomial degree of elements.
  E.set_initial_poly_degree(init_p);

  // Set material markers (also checks compatibility with the mesh file).
  E.set_material_markers(mat_markers);

  // Set permittivity array.
  E.set_permittivity_array(permittivity_array);

  // Set charge density array.
  E.set_charge_density_array(charge_density_array);

  // Set VALUE boundary markers (also check with the mesh file).
  E.set_boundary_markers_value(bc_markers_value);

  // Set boundary values.
  E.set_boundary_values(bc_values);

  // Set DERIVATIVE boundary markers (also check with the mesh file).
  E.set_boundary_markers_derivative(bc_markers_derivative);

  // Set boundary derivatives.
  E.set_boundary_values(bc_derivatives);


  /*** SOLVE THE PROBLEM ***/

  Solution phi;
  bool success = E.calculate(&phi);
  if (!success) error("Computation failed.");

  /*** SHOW THE SOLUTION ***/

  ScalarView view("Solution", new WinGeom(0, 0, 440, 350));
  view.show(&phi);

  // Compute and show gradient magnitude.
  // (Note that the gradient at the re-entrant
  // corner needs to be truncated for visualization purposes.)
  ScalarView gradview("Gradient", new WinGeom(450, 0, 400, 350));
  MagFilter grad(Tuple<MeshFunction *>(&phi, &phi), Tuple<int>(H2D_FN_DX, H2D_FN_DY));
  gradview.show(&grad);

  // Wait for the views to be closed.
  View::wait();

  return 1;
}
