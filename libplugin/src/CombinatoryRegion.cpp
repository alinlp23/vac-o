#include <mili/mili.h>
#include "CombinatoryRegion.h"

CombinatoryRegion::CombinatoryRegion(SeqIndex start, SeqIndex end) :
        start(start), end(end), constraints(), base_sequence()
{}

void CombinatoryRegion::set_base_sequence(const NucSequence& sequence)
{
    base_sequence = sequence;
}

void CombinatoryRegion::add_constraint(SeqIndex start, SeqIndex end)
{
    Constraint* c = new Constraint;
    c->start = start;
    c->end = end;
    insert_into(constraints, c);
}

void CombinatoryRegion::get_bounds(SeqIndex& s, SeqIndex& e)
{
    s = start;
    e = end;
}