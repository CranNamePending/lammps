/* ----------------------------------------------------------------------
   LAMMPS - Large-scale Atomic/Molecular Massively Parallel Simulator
   http://lammps.sandia.gov, Sandia National Laboratories
   Steve Plimpton, sjplimp@sandia.gov

   Copyright (2003) Sandia Corporation.  Under the terms of Contract
   DE-AC04-94AL85000 with Sandia Corporation, the U.S. Government retains
   certain rights in this software.  This software is distributed under
   the GNU General Public License.

   See the README file in the top-level LAMMPS directory.
------------------------------------------------------------------------- */

#include "compute_meso_nu_atom.h"
#include <cstring>
#include "atom.h"
#include "update.h"
#include "modify.h"
#include "comm.h"
#include "memory.h"
#include "error.h"

using namespace LAMMPS_NS;

/* ---------------------------------------------------------------------- */

ComputeMesoNuAtom::ComputeMesoNuAtom(LAMMPS *lmp, int narg, char **arg) :
  Compute(lmp, narg, arg)
{
  if (narg != 3) error->all(FLERR,"Illegal compute meso/nu/atom command");
  if (atom->nu_flag != 1) error->all(FLERR,"compute meso/nu/atom command requires atom_style with density (e.g. meso)");

  peratom_flag = 1;
  size_peratom_cols = 0;

  nmax = 0;
  nuVector = NULL;
}

/* ---------------------------------------------------------------------- */

ComputeMesoNuAtom::~ComputeMesoNuAtom()
{
  memory->sfree(nuVector);
}

/* ---------------------------------------------------------------------- */

void ComputeMesoNuAtom::init()
{

  int count = 0;
  for (int i = 0; i < modify->ncompute; i++)
    if (strcmp(modify->compute[i]->style,"nuVector/atom") == 0) count++;
  if (count > 1 && comm->me == 0)
    error->warning(FLERR,"More than one compute nuVector/atom");
}

/* ---------------------------------------------------------------------- */

void ComputeMesoNuAtom::compute_peratom()
{
  invoked_peratom = update->ntimestep;

  // grow nuVector array if necessary

  if (atom->nmax > nmax) {
    memory->sfree(nuVector);
    nmax = atom->nmax;
    nuVector = (double *) memory->smalloc(nmax*sizeof(double),"atom:nuVector");
    vector_atom = nuVector;
  }

  // compute kinetic energy for each atom in group

  double *nu = atom->nu;
  int *mask = atom->mask;
  int nlocal = atom->nlocal;

    for (int i = 0; i < nlocal; i++) {
      if (mask[i] & groupbit) {
              nuVector[i] = nu[i];
      }
      else {
              nuVector[i] = 0.0;
      }
    }
}

/* ----------------------------------------------------------------------
   memory usage of local atom-based array
------------------------------------------------------------------------- */

double ComputeMesoNuAtom::memory_usage()
{
  double bytes = nmax * sizeof(double);
  return bytes;
}
