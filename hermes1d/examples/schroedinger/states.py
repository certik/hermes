from numpy import array, zeros, arange
from scipy.interpolate import InterpolatedUnivariateSpline, UnivariateSpline
from h5py import File

class InterpolatedFunction(object):

    def __init__(self, x, y):
        self._x = x
        self._y = y

    def __call__(self, a):
        return array([self.get_value(x) for x in a])

    def get_value(self, v):
        _i = -1
        for i in range(len(self._x)):
            if v < self._x[i]:
                _i = i
                break
        return self._y[_i]

def construct_density(Es, data):
    radial_mesh = arange(0, 20, 0.1)
    density1 = zeros(len(radial_mesh), "d")
    density2 = zeros(len(radial_mesh), "d")
    for E, i in Es:
        print i
        E, n, l, eig, r = data[i]
        s = InterpolatedFunction(r, eig)
        y = s(radial_mesh)
        if n == l + 1:
            density1 += y**2
        else:
            density2 += y**2
    return radial_mesh, density1, density2

f = File("data2.hdf5")
max_l = int(array(f["/dft/max_l"]))
states = {}
eigs = {}
r = {}
for l in range(max_l+1):
    states[l] = array(f["/dft/%d/E" % l])
    r[l] = array(f["/dft/%d/r" % l])
    eigs[l] = array(f["/dft/%d/eigs" % l])

orbital_name = ["s", "p", "d", "f", "g", "h", "i", "k", "l", "m", "n",
        "o", "p"]

my_states = []
for l in range(max_l):
    n = 1 + l
    for E, eig in zip(states[l], eigs[l]):
        my_states.append((E, n, l, eig, r[l]))
        n += 1

print "-"*80
total_electrons = 0
for E, n, l, eig, r in my_states:
    print "(l=%d, n=%d)" % (l, n),
    print "%d%s" % (n, orbital_name[l]),
    print "E=%f" % E,
    deg = 2*(2*l+1)
    print "degeneracy 2*(2*l+1) = %d" % deg,
    total_electrons += deg
    print "total electrons = %d" % total_electrons
    n += 1

print "-"*80
print "Sorted by energy"
my_states.sort(key=lambda state: state[0])
total_electrons = 0
for E, n, l, eig, r in my_states:
    print "(l=%d, n=%d)" % (l, n),
    print "%d%s" % (n, orbital_name[l]),
    print "E=%f" % E,
    deg = 2*(2*l+1)
    print "degeneracy 2*(2*l+1) = %d" % deg,
    total_electrons += deg
    print "total electrons = %d" % total_electrons
    n += 1

Es = []
for i, (E, n, l, eig, r) in enumerate(my_states):
    fn = 2*(2*l + 1)
    Es.extend([(E, i)] * fn)
Es = Es[:240]

r, R1, R2 = construct_density(Es, my_states)
from pylab import plot, show, legend
plot(r, R1, label="n = l + 1")
plot(r, R2, label="n = l + 2")
plot(r, R1 + R2, label="total")
legend()
show()
