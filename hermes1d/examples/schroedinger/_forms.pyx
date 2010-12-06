from hermes1d.h1d_wrapper.h1d_wrapper cimport Mesh
from hermes_common._hermes_common cimport Matrix

from numpy import array, empty, linspace
from scipy.interpolate import InterpolatedUnivariateSpline
from h5py import File

cimport cython

s = None

def assemble_schroedinger(Mesh mesh, Matrix A, Matrix B, l=0, Z=1,
        eqn_type=None):
    cdef int equation_type
    if eqn_type == "R":
        equation_type = c_eqn_type_R
    elif eqn_type == "rR":
        equation_type = c_eqn_type_rR
    else:
        raise ValueError("Unknown equation type")

    f = File("data.hdf5")
    r = array(f["/dft/r"])
    zeff = array(f["/dft/zeff"])
    global s
    s = InterpolatedUnivariateSpline(r, zeff)

    c_assemble_schroedinger(mesh.thisptr, A.thisptr, B.thisptr, l, Z,
            equation_type)

cdef api double Z_eff(double x):
    return s(x)

#cdef api double potential_V(double r) nogil:
#    return r**2

@cython.cdivision(True)
cdef api double potential_V(double r) nogil:
    cdef double R1 = 5.24399001075
    cdef double R2 = 8.13527098965
    cdef double rho0 = 1.5
    cdef double result = 0.
    if r < R1:
        result = 0
    elif r < R2:
        result = -rho0
    else:
        result = 0
        #result = -1/r
    #result += -54./r
    return result

def potential_python(r):
    return potential_V(r)