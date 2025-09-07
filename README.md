# cftsolver - A Classical Field Theory Solver

I've always been a visual learner. 
We can solve Quantum Field Theory (QFT) by doing quantum mechanics - computing the S-matrix from the path integral, a sort of overlap integral between two definite states.
What about solving the underlying classical field theory before quantizing? This tool aims to visualize interacting theories by solving the Euler-Lagrange equations of motion (EoM) explicitly for a set of input field configurations. This is effectively a system of coupled partial differential equations on a lattice. We will first start by investigating free field theories and then graduate to interacting ones, like scalar QED.

### TODO
* implement field classes
* euler lagrange equations of motion: scalar QED + gauge fixing
* add modules for 1-D and 2-D solvers
* test OpenGL

Long term:
* test scattering
* test decays
* make interactive in web browser embedding


# Modules

## Scalar-Yukawa Theory
Let's first start with a simple theory of a massive, real scalar field $\phi$
without any interaction. It's Lagrangian can be written as
$$\mathcal{L} = \frac{1}{2}(\partial_\mu \phi) (\partial^\mu \phi) - \frac{1}{2}m^2 \phi^2$$
With the Euler-Lagrange equations, this leads to the Klein-Gordon equation
of motion for the field $\phi$,
$$(\Box + m^2) \phi = 0$$

If we want to simulate this with finite difference methods, there are a few
routes to take. The simplest is to open up the KG equation and discretize
the derivatives with central difference, working for now in 1 space and 1 time
dimension:
$$\partial_{t}^2 \phi \to \frac{\phi(t_{i+1}) - 2 \phi(t_{i}) + \phi(t_{i-1})}{\Delta t^2}$$
$$\partial_{x}^2 \phi \to \frac{\phi(x_{i+1}) - 2 \phi(x_{i}) + \phi(x_{i-1})}{\Delta x^2}$$
Where we are now describing the field over a N-dimensional space lattice with
coordinates $x_{i}$ of spacing $\Delta x$ and time steps $\Delta t$ over time
coordinates $t_{i}$. This permits us to solve for the "push" of $\phi$
to the next time step;
$$\phi(x_{i},t_{i+1}) \simeq 2 \phi(x_{i},t_{i}) - \phi(x_{i},t_{i-1}) + (\partial^2_{x_{i}}\phi(x_{i},t_{i}) - m^2\phi(x_{i},t_{i})) (\Delta t)^2$$

From this equation we can immediately recognize that, just like solving any
PDE, we require some boundary condition information; to kick things off we
require data on the fields at two time slices -- the present slice and the
one before -- and we also need spatial boundary conditions at the edges of our
discretized space in order to compute the values of the field and its derivatives.

## Scalar QED
```wip```

## Scalar QED with Massive Photons
```wip```

## Scalar QED with a Higgs Potential
```wip```
