// #define DEBUG 1
/* generated by common/NeuronClass.jinja2 *//*
 *  iaf_psc_exp_wta__with_stdp_solo.cpp
 *
 *  This file is part of NEST.
 *
 *  Copyright (C) 2004 The NEST Initiative
 *
 *  NEST is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  NEST is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with NEST.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  Generated from NESTML at time: 2022-09-06 14:45:58.363804
**/

// C++ includes:
#include <limits>

// Includes from libnestutil:
#include "numerics.h"

// Includes from nestkernel:
#include "exceptions.h"
#include "kernel_manager.h"
#include "universal_data_logger_impl.h"

// Includes from sli:
#include "dict.h"
#include "dictutils.h"
#include "doubledatum.h"
#include "integerdatum.h"
#include "lockptrdatum.h"

#include "iaf_psc_exp_wta__with_stdp_solo.h"

// ---------------------------------------------------------------------------
//   Recordables map
// ---------------------------------------------------------------------------
nest::RecordablesMap<iaf_psc_exp_wta__with_stdp_solo> iaf_psc_exp_wta__with_stdp_solo::recordablesMap_;
namespace nest
{

  // Override the create() method with one call to RecordablesMap::insert_()
  // for each quantity to be recorded.
template <> void RecordablesMap<iaf_psc_exp_wta__with_stdp_solo>::create()
  {
    // add state variables to recordables map
   insert_(iaf_psc_exp_wta__with_stdp_solo_names::_V_m, &iaf_psc_exp_wta__with_stdp_solo::get_V_m);
   insert_(iaf_psc_exp_wta__with_stdp_solo_names::_a_pre__for_stdp_solo, &iaf_psc_exp_wta__with_stdp_solo::get_a_pre__for_stdp_solo);
   insert_(iaf_psc_exp_wta__with_stdp_solo_names::_a_post__for_stdp_solo, &iaf_psc_exp_wta__with_stdp_solo::get_a_post__for_stdp_solo);
   insert_(iaf_psc_exp_wta__with_stdp_solo_names::_I_kernel_exc__X__exc_spikes, &iaf_psc_exp_wta__with_stdp_solo::get_I_kernel_exc__X__exc_spikes);
   insert_(iaf_psc_exp_wta__with_stdp_solo_names::_I_kernel_inh__X__inh_spikes, &iaf_psc_exp_wta__with_stdp_solo::get_I_kernel_inh__X__inh_spikes);
   insert_(iaf_psc_exp_wta__with_stdp_solo_names::_normalization_sum, &iaf_psc_exp_wta__with_stdp_solo::get_normalization_sum);

    // Add vector variables
  }
}

// ---------------------------------------------------------------------------
//   Default constructors defining default parameters and state
//   Note: the implementation is empty. The initialization is of variables
//   is a part of iaf_psc_exp_wta__with_stdp_solo's constructor.
// ---------------------------------------------------------------------------

iaf_psc_exp_wta__with_stdp_solo::Parameters_::Parameters_()
{
}

iaf_psc_exp_wta__with_stdp_solo::State_::State_()
{
}

// ---------------------------------------------------------------------------
//   Parameter and state extractions and manipulation functions
// ---------------------------------------------------------------------------

iaf_psc_exp_wta__with_stdp_solo::Buffers_::Buffers_(iaf_psc_exp_wta__with_stdp_solo &n):
  logger_(n)
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

iaf_psc_exp_wta__with_stdp_solo::Buffers_::Buffers_(const Buffers_ &, iaf_psc_exp_wta__with_stdp_solo &n):
  logger_(n)
{
  // Initialization of the remaining members is deferred to init_buffers_().
}

// ---------------------------------------------------------------------------
//   Default constructor for node
// ---------------------------------------------------------------------------

iaf_psc_exp_wta__with_stdp_solo::iaf_psc_exp_wta__with_stdp_solo():ArchivingNode(), P_(), S_(), B_(*this)
{
  const double __resolution = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the resolution() function
  pre_run_hook();
  // initial values for parameters
    /* generated by directives/MemberInitialization.jinja2 */
    P_.C_m = 250; // as pF
    /* generated by directives/MemberInitialization.jinja2 */
    P_.tau_m = 20; // as ms
    /* generated by directives/MemberInitialization.jinja2 */
    P_.tau_syn_inh = 2; // as ms
    /* generated by directives/MemberInitialization.jinja2 */
    P_.tau_syn_exc = 2; // as ms
    /* generated by directives/MemberInitialization.jinja2 */
    P_.E_L = 0; // as mV
    /* generated by directives/MemberInitialization.jinja2 */
    P_.V_reset = 0 - P_.E_L; // as mV
    /* generated by directives/MemberInitialization.jinja2 */
    P_.R_max = 100; // as Hz
    /* generated by directives/MemberInitialization.jinja2 */
    P_.tau_tr_pre__for_stdp_solo = 15; // as ms
    /* generated by directives/MemberInitialization.jinja2 */
    P_.tau_tr_post__for_stdp_solo = 30; // as ms
  // initial values for state variables
    /* generated by directives/MemberInitialization.jinja2 */
    S_.r = 0; // as integer
    /* generated by directives/MemberInitialization.jinja2 */
    S_.V_m = 0; // as mV
    /* generated by directives/MemberInitialization.jinja2 */
    S_.a_pre__for_stdp_solo = 0.0; // as real
    /* generated by directives/MemberInitialization.jinja2 */
    S_.a_post__for_stdp_solo = 0.0; // as real
    /* generated by directives/MemberInitialization.jinja2 */
    S_.I_kernel_exc__X__exc_spikes = 0; // as real
    /* generated by directives/MemberInitialization.jinja2 */
    S_.I_kernel_inh__X__inh_spikes = 0; // as real
  recordablesMap_.create();
  /* normalization sum for rate */
  V_.normalization_sum = 0.;
  // state variables for archiving state for paired synapse
  n_incoming_ = 0;
  max_delay_ = 0;
  last_spike_ = -1.;

  // cache initial values
  a_pre__for_stdp_solo__iv = get_a_pre__for_stdp_solo();
  a_post__for_stdp_solo__iv = get_a_post__for_stdp_solo();
}

// ---------------------------------------------------------------------------
//   Copy constructor for node
// ---------------------------------------------------------------------------

iaf_psc_exp_wta__with_stdp_solo::iaf_psc_exp_wta__with_stdp_solo(const iaf_psc_exp_wta__with_stdp_solo& __n):
  ArchivingNode(), P_(__n.P_), S_(__n.S_), B_(__n.B_, *this) {

  // copy parameter struct P_
  P_.C_m = __n.P_.C_m;
  P_.tau_m = __n.P_.tau_m;
  P_.tau_syn_inh = __n.P_.tau_syn_inh;
  P_.tau_syn_exc = __n.P_.tau_syn_exc;
  P_.E_L = __n.P_.E_L;
  P_.V_reset = __n.P_.V_reset;
  P_.R_max = __n.P_.R_max;
  P_.tau_tr_pre__for_stdp_solo = __n.P_.tau_tr_pre__for_stdp_solo;
  P_.tau_tr_post__for_stdp_solo = __n.P_.tau_tr_post__for_stdp_solo;

  // copy state struct S_
  S_.r = __n.S_.r;
  S_.V_m = __n.S_.V_m;
  S_.a_pre__for_stdp_solo = __n.S_.a_pre__for_stdp_solo;
  S_.a_post__for_stdp_solo = __n.S_.a_post__for_stdp_solo;
  S_.I_kernel_exc__X__exc_spikes = __n.S_.I_kernel_exc__X__exc_spikes;
  S_.I_kernel_inh__X__inh_spikes = __n.S_.I_kernel_inh__X__inh_spikes;


  // copy internals V_
  V_.__h = __n.V_.__h;
  V_.__P__V_m__V_m = __n.V_.__P__V_m__V_m;
  V_.__P__V_m__I_kernel_exc__X__exc_spikes = __n.V_.__P__V_m__I_kernel_exc__X__exc_spikes;
  V_.__P__V_m__I_kernel_inh__X__inh_spikes = __n.V_.__P__V_m__I_kernel_inh__X__inh_spikes;
  V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo = __n.V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo;
  V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo = __n.V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo;
  V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes = __n.V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;
  V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes = __n.V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;
  V_.normalization_sum = __n.V_.normalization_sum;
  n_incoming_ = __n.n_incoming_;
  max_delay_ = __n.max_delay_;
  last_spike_ = __n.last_spike_;

  // cache initial values
  a_pre__for_stdp_solo__iv = get_a_pre__for_stdp_solo();
  a_post__for_stdp_solo__iv = get_a_post__for_stdp_solo();
}

// ---------------------------------------------------------------------------
//   Destructor for node
// ---------------------------------------------------------------------------

iaf_psc_exp_wta__with_stdp_solo::~iaf_psc_exp_wta__with_stdp_solo()
{
}

// ---------------------------------------------------------------------------
//   Node initialization functions
// ---------------------------------------------------------------------------

void iaf_psc_exp_wta__with_stdp_solo::init_buffers_()
{
  get_exc_spikes().clear(); //includes resize
  get_inh_spikes().clear(); //includes resize
  get_I_stim().clear(); //includes resize
  B_.logger_.reset(); // includes resize
}

void iaf_psc_exp_wta__with_stdp_solo::recompute_internal_variables(bool exclude_timestep) {
  const double __resolution = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the resolution() function

  if (exclude_timestep) {
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__V_m__V_m = std::exp((-(V_.__h)) / P_.tau_m); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__V_m__I_kernel_exc__X__exc_spikes = P_.tau_m * P_.tau_syn_exc * ((-(std::exp(V_.__h / P_.tau_m))) + std::exp(V_.__h / P_.tau_syn_exc)) * std::exp((-(V_.__h)) * (P_.tau_m + P_.tau_syn_exc) / (P_.tau_m * P_.tau_syn_exc)) / (P_.C_m * (P_.tau_m - P_.tau_syn_exc)); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__V_m__I_kernel_inh__X__inh_spikes = P_.tau_m * P_.tau_syn_inh * (std::exp(V_.__h / P_.tau_m) - std::exp(V_.__h / P_.tau_syn_inh)) * std::exp((-(V_.__h)) * (P_.tau_m + P_.tau_syn_inh) / (P_.tau_m * P_.tau_syn_inh)) / (P_.C_m * (P_.tau_m - P_.tau_syn_inh)); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo = std::exp((-(V_.__h)) / P_.tau_tr_pre__for_stdp_solo); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo = std::exp((-(V_.__h)) / P_.tau_tr_post__for_stdp_solo); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes = std::exp((-(V_.__h)) / P_.tau_syn_exc); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes = std::exp((-(V_.__h)) / P_.tau_syn_inh); // as real
  }
  else {
    // internals V_
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__h = __resolution; // as ms
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__V_m__V_m = std::exp((-(V_.__h)) / P_.tau_m); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__V_m__I_kernel_exc__X__exc_spikes = P_.tau_m * P_.tau_syn_exc * ((-(std::exp(V_.__h / P_.tau_m))) + std::exp(V_.__h / P_.tau_syn_exc)) * std::exp((-(V_.__h)) * (P_.tau_m + P_.tau_syn_exc) / (P_.tau_m * P_.tau_syn_exc)) / (P_.C_m * (P_.tau_m - P_.tau_syn_exc)); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__V_m__I_kernel_inh__X__inh_spikes = P_.tau_m * P_.tau_syn_inh * (std::exp(V_.__h / P_.tau_m) - std::exp(V_.__h / P_.tau_syn_inh)) * std::exp((-(V_.__h)) * (P_.tau_m + P_.tau_syn_inh) / (P_.tau_m * P_.tau_syn_inh)) / (P_.C_m * (P_.tau_m - P_.tau_syn_inh)); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo = std::exp((-(V_.__h)) / P_.tau_tr_pre__for_stdp_solo); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo = std::exp((-(V_.__h)) / P_.tau_tr_post__for_stdp_solo); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes = std::exp((-(V_.__h)) / P_.tau_syn_exc); // as real
      /* generated by directives/MemberInitialization.jinja2 */
      V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes = std::exp((-(V_.__h)) / P_.tau_syn_inh); // as real
  }
}
void iaf_psc_exp_wta__with_stdp_solo::pre_run_hook() {
  B_.logger_.init();

  recompute_internal_variables();

  // buffers B_
}

// ---------------------------------------------------------------------------
//   Update and spike handling functions
// ---------------------------------------------------------------------------


void iaf_psc_exp_wta__with_stdp_solo::update(nest::Time const & origin,const long from, const long to)
{
  const double __resolution = nest::Time::get_resolution().get_ms();  // do not remove, this is necessary for the resolution() function

    const size_t buffer_size = nest::kernel().connection_manager.get_min_delay();
    const double wfr_tol = nest::kernel().simulation_manager.get_wfr_tol();
    bool wfr_tol_exceeded = false;

    // allocate memory to store rates to be sent by rate events
    std::vector< double > new_voltage( buffer_size, 0.0 );

  for ( long lag = from ; lag < to ; ++lag )
  {
    B_.exc_spikes_grid_sum_ = get_exc_spikes().get_value(lag);
    B_.inh_spikes_grid_sum_ = get_inh_spikes().get_value(lag);
    B_.I_stim_grid_sum_ = get_I_stim().get_value(lag);

    // NESTML generated code for the update block:/* generated by directives/Block.jinja2 */ /* generated by directives/Statement.jinja2 */ /* generated by directives/SmallStatement.jinja2 */ /* generated by directives/FunctionCall.jinja2 */ /* generated by directives/AnalyticIntegrationStep_begin.jinja2 */
  double V_m__tmp = (P_.C_m * (get_I_kernel_exc__X__exc_spikes() * V_.__P__V_m__I_kernel_exc__X__exc_spikes + get_I_kernel_inh__X__inh_spikes() * V_.__P__V_m__I_kernel_inh__X__inh_spikes) + B_.I_stim_grid_sum_ * P_.tau_m + V_.__P__V_m__V_m * (P_.C_m * get_V_m() - B_.I_stim_grid_sum_ * P_.tau_m)) / P_.C_m;
  double I_kernel_exc__X__exc_spikes__tmp = get_I_kernel_exc__X__exc_spikes() * V_.__P__I_kernel_exc__X__exc_spikes__I_kernel_exc__X__exc_spikes;
  double I_kernel_inh__X__inh_spikes__tmp = get_I_kernel_inh__X__inh_spikes() * V_.__P__I_kernel_inh__X__inh_spikes__I_kernel_inh__X__inh_spikes;
  /* replace analytically solvable variables with precisely integrated values  *//* generated by directives/AnalyticIntegrationStep_end.jinja2 */
  S_.V_m = V_m__tmp;
  S_.I_kernel_exc__X__exc_spikes = I_kernel_exc__X__exc_spikes__tmp;
  S_.I_kernel_inh__X__inh_spikes = I_kernel_inh__X__inh_spikes__tmp;/* generated by directives/ApplySpikesFromBuffers.jinja2 */ /* generated by directives/Assignment.jinja2 */
      S_.I_kernel_exc__X__exc_spikes += (B_.exc_spikes_grid_sum_) / (1.0);/* generated by directives/Assignment.jinja2 */
      S_.I_kernel_inh__X__inh_spikes += (B_.inh_spikes_grid_sum_) / (1.0);/* generated by directives/Statement.jinja2 */ /* generated by directives/SmallStatement.jinja2 */ /* generated by directives/Declaration.jinja2 */
  double rate = P_.R_max * std::exp(get_V_m() / 1.0) / (V_.normalization_sum + std::exp(get_V_m()));/* generated by directives/Statement.jinja2 */ /* generated by directives/SmallStatement.jinja2 */ /* generated by directives/Declaration.jinja2 */
  double p = __resolution * rate / 1000;/* generated by directives/Statement.jinja2 */ /* generated by directives/CompoundStatement.jinja2 */ /* generated by directives/IfStatement.jinja2 */
  if (((0) + (1) * nest::get_vp_specific_rng( get_thread() )->drand())<=p)
  {/* generated by directives/Block.jinja2 */ /* generated by directives/Statement.jinja2 */ /* generated by directives/SmallStatement.jinja2 */ /* generated by directives/FunctionCall.jinja2 */
  set_spiketime(nest::Time::step(origin.get_steps()+lag+1));
  nest::SpikeEvent se;
  nest::kernel().event_delivery_manager.send(*this, se, lag);
  }

    // voltage logging
    B_.logger_.record_data(origin.get_steps() + lag);

    new_voltage[ lag ] = S_.V_m;
  }
  // Send rate-neuron-event
  //std::cout << "Sending InstantaneousRateConnectionEvent..." << std::endl << std::flush;

  nest::InstantaneousRateConnectionEvent u_t_event;
  u_t_event.set_coeffarray( new_voltage );
  nest::kernel().event_delivery_manager.send_secondary( *this, u_t_event );

  // could reset the normalization factor to 0 here
  V_.normalization_sum = 0.;
}

// Do not move this function as inline to h-file. It depends on
// universal_data_logger_impl.h being included here.
void iaf_psc_exp_wta__with_stdp_solo::handle(nest::DataLoggingRequest& e)
{
  B_.logger_.handle(e);
}

void iaf_psc_exp_wta__with_stdp_solo::handle(nest::SpikeEvent &e)
{
  assert(e.get_delay_steps() > 0);
  const double weight = e.get_weight();
  const double multiplicity = e.get_multiplicity();
  // this port receives excitatory spikes
  if ( weight >= 0.0 )
  {
    get_exc_spikes().
        add_value(e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin()),
                       weight * multiplicity );
  }
  // this port receives inhibitory spikes
  if ( weight < 0.0 )
  {
    get_inh_spikes().
        add_value(e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin()),
                  -weight * multiplicity );
  }
}

void iaf_psc_exp_wta__with_stdp_solo::handle(nest::CurrentEvent& e)
{
  assert(e.get_delay_steps() > 0);

  const double current = e.get_current();     // we assume that in NEST, this returns a current in pA
  const double weight = e.get_weight();
  get_I_stim().add_value(
               e.get_rel_delivery_steps( nest::kernel().simulation_manager.get_slice_origin()),
               weight * current );
}

void iaf_psc_exp_wta__with_stdp_solo::handle(nest::InstantaneousRateConnectionEvent& e)
{
    // std::cout << "Received InstantaneousRateConnectionEvent " << std::endl << std::flush;

    size_t i = 0;
    std::vector< unsigned int >::iterator it = e.begin();
    // The call to get_coeffvalue( it ) in this loop also advances the iterator it
    while ( it != e.end() )
    {
        V_.normalization_sum += exp(e.get_coeffvalue(it));
//        B_.instant_rates_ex_[i] += weight * e.get_coeffvalue(it);
//        std::cout << "Received InstantaneousRateConnectionEvent - u(t) of presyn neuron:"
//            << e.get_coeffvalue(it) << std::endl << std::flush;
    }
}


inline double
iaf_psc_exp_wta__with_stdp_solo::get_spiketime_ms() const
{
  return last_spike_;
}


void
iaf_psc_exp_wta__with_stdp_solo::register_stdp_connection( double t_first_read, double delay )
{
  // Mark all entries in the deque, which we will not read in future as read by
  // this input input, so that we safely increment the incoming number of
  // connections afterwards without leaving spikes in the history.
  // For details see bug #218. MH 08-04-22

  for ( std::deque< histentry__iaf_psc_exp_wta__with_stdp_solo >::iterator runner = history_.begin();
        runner != history_.end() and ( t_first_read - runner->t_ > -1.0 * nest::kernel().connection_manager.get_stdp_eps() );
        ++runner )
  {
    ( runner->access_counter_ )++;
  }

  n_incoming_++;

  max_delay_ = std::max( delay, max_delay_ );
}


void
iaf_psc_exp_wta__with_stdp_solo::get_history__( double t1,
  double t2,
  std::deque< histentry__iaf_psc_exp_wta__with_stdp_solo >::iterator* start,
  std::deque< histentry__iaf_psc_exp_wta__with_stdp_solo >::iterator* finish )
{
  *finish = history_.end();
  if ( history_.empty() )
  {
    *start = *finish;
    return;
  }
  std::deque< histentry__iaf_psc_exp_wta__with_stdp_solo >::reverse_iterator runner = history_.rbegin();
  const double t2_lim = t2 + nest::kernel().connection_manager.get_stdp_eps();
  const double t1_lim = t1 + nest::kernel().connection_manager.get_stdp_eps();
  while ( runner != history_.rend() and runner->t_ >= t2_lim )
  {
    ++runner;
  }
  *finish = runner.base();
  while ( runner != history_.rend() and runner->t_ >= t1_lim )
  {
    runner->access_counter_++;
    ++runner;
  }
  *start = runner.base();
}

void
iaf_psc_exp_wta__with_stdp_solo::set_spiketime( nest::Time const& t_sp, double offset )
{
    ArchivingNode::set_spiketime( t_sp, offset );

    unsigned int num_transferred_variables = 0;
    ++num_transferred_variables;
    ++num_transferred_variables;

    const double t_sp_ms = t_sp.get_ms() - offset;

    if ( n_incoming_ )
    {
        // prune all spikes from history which are no longer needed
        // only remove a spike if:
        // - its access counter indicates it has been read out by all connected
        //     STDP synapses, and
        // - there is another, later spike, that is strictly more than
        //     (max_delay_ + eps) away from the new spike (at t_sp_ms)
        while ( history_.size() > 1 )
        {
            const double next_t_sp = history_[ 1 ].t_;
            if ( history_.front().access_counter_ >= n_incoming_ * num_transferred_variables
                and t_sp_ms - next_t_sp > max_delay_ + nest::kernel().connection_manager.get_stdp_eps() )
            {
                history_.pop_front();
            }
            else
            {
                break;
            }
        }

        if (history_.size() > 0) {
            assert(history_.back().t_ == last_spike_);
            S_.a_post__for_stdp_solo = history_.back().a_post__for_stdp_solo_;
            S_.a_pre__for_stdp_solo = history_.back().a_pre__for_stdp_solo_;
        }
        else {
            S_.a_post__for_stdp_solo = 0.; // initial value for convolution is always 0
            S_.a_pre__for_stdp_solo = 0.; // initial value for convolution is always 0
        }


        /**
         * update state variables transferred from synapse from `last_spike_` to `t_sp_ms`
        **/

        const double old___h = V_.__h;
        V_.__h = t_sp_ms - last_spike_;
        if (V_.__h > 1E-12) {
          recompute_internal_variables(true);
      /* generated by directives/AnalyticIntegrationStep_begin.jinja2 */
      double a_post__for_stdp_solo__tmp = V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo * get_a_post__for_stdp_solo();
      double a_pre__for_stdp_solo__tmp = V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo * get_a_pre__for_stdp_solo();
      /* replace analytically solvable variables with precisely integrated values  *//* generated by directives/AnalyticIntegrationStep_end.jinja2 */
      S_.a_post__for_stdp_solo = a_post__for_stdp_solo__tmp;
      S_.a_pre__for_stdp_solo = a_pre__for_stdp_solo__tmp;
        V_.__h = old___h;
        recompute_internal_variables(true);
      }

        /**
         * apply spike updates
        **/

    last_spike_ = t_sp_ms;
    history_.push_back( histentry__iaf_psc_exp_wta__with_stdp_solo( last_spike_
    , get_a_post__for_stdp_solo()
    , get_a_pre__for_stdp_solo()
, 0
 ) );
  }
  else
  {
    last_spike_ = t_sp_ms;
  }
}


void
iaf_psc_exp_wta__with_stdp_solo::clear_history()
{
  last_spike_ = -1.0;
  history_.clear();
}




double
iaf_psc_exp_wta__with_stdp_solo::get_a_pre__for_stdp_solo( double t, const bool before_increment )
{
#ifdef DEBUG
  std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_pre__for_stdp_solo: getting value at t = " << t << std::endl;
#endif

  // case when the neuron has not yet spiked
  if ( history_.empty() )
  {
#ifdef DEBUG
    std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_pre__for_stdp_solo: \thistory empty, returning initial value = " << a_pre__for_stdp_solo__iv << std::endl;
#endif
    // return initial value
    return a_pre__for_stdp_solo__iv;
  }

  // search for the latest post spike in the history buffer that came strictly before `t`
  int i = history_.size() - 1;
  double eps = 0.;
  if ( before_increment ) {
   eps = nest::kernel().connection_manager.get_stdp_eps();
  }
  while ( i >= 0 )
  {
    if ( t - history_[ i ].t_ >= eps )
    {
#ifdef DEBUG
      std::cout<<"iaf_psc_exp_wta__with_stdp_solo::get_a_pre__for_stdp_solo: \tspike occurred at history[i].t_ = " << history_[i].t_ << std::endl;
#endif
      S_.a_pre__for_stdp_solo = history_[ i ].a_pre__for_stdp_solo_;
      S_.a_post__for_stdp_solo = history_[ i ].a_post__for_stdp_solo_;

      /**
       * update state variables transferred from synapse from `history[i].t_` to `t`
      **/

      if ( t - history_[ i ].t_ >= nest::kernel().connection_manager.get_stdp_eps() )
      {
        const double old___h = V_.__h;
        V_.__h = t - history_[i].t_;
        assert(V_.__h > 0);
        recompute_internal_variables(true);
      /* generated by directives/AnalyticIntegrationStep_begin.jinja2 */
      double a_post__for_stdp_solo__tmp = V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo * get_a_post__for_stdp_solo();
      double a_pre__for_stdp_solo__tmp = V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo * get_a_pre__for_stdp_solo();
      /* replace analytically solvable variables with precisely integrated values  *//* generated by directives/AnalyticIntegrationStep_end.jinja2 */
      S_.a_post__for_stdp_solo = a_post__for_stdp_solo__tmp;
      S_.a_pre__for_stdp_solo = a_pre__for_stdp_solo__tmp;

        V_.__h = old___h;
        recompute_internal_variables(true);
      }

#ifdef DEBUG
      std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_pre__for_stdp_solo: \treturning " << get_a_pre__for_stdp_solo() << std::endl;
#endif
      return get_a_pre__for_stdp_solo();       // type: double
    }
    --i;
  }

  // this case occurs when the trace was requested at a time precisely at that of the first spike in the history
  if ( (!before_increment) && t == history_[ 0 ].t_)
  {
    S_.a_pre__for_stdp_solo = history_[ 0 ].a_pre__for_stdp_solo_;
    S_.a_post__for_stdp_solo = history_[ 0 ].a_post__for_stdp_solo_;

#ifdef DEBUG
    std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_pre__for_stdp_solo: \ttrace requested at exact time of history entry 0, returning " << get_a_pre__for_stdp_solo() << std::endl;
#endif
    return get_a_pre__for_stdp_solo();
  }

  // this case occurs when the trace was requested at a time before the first spike in the history
  // return initial value propagated in time
#ifdef DEBUG
  std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_pre__for_stdp_solo: \tfall-through, returning initial value = " << a_pre__for_stdp_solo__iv << std::endl;
#endif

  if (t == 0.) {
    return 0.;  // initial value for convolution is always 0
  }

  // set to initial value
  S_.a_pre__for_stdp_solo = 0.;  // initial value for convolution is always 0
  S_.a_post__for_stdp_solo = 0.;  // initial value for convolution is always 0

  // propagate in time
  const double old___h = V_.__h;
  V_.__h = t;   // from time 0 to the requested time
  assert(V_.__h > 0);
  recompute_internal_variables(true);
  /* generated by directives/AnalyticIntegrationStep_begin.jinja2 */
  double a_post__for_stdp_solo__tmp = V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo * get_a_post__for_stdp_solo();
  double a_pre__for_stdp_solo__tmp = V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo * get_a_pre__for_stdp_solo();
  /* replace analytically solvable variables with precisely integrated values  *//* generated by directives/AnalyticIntegrationStep_end.jinja2 */
  S_.a_post__for_stdp_solo = a_post__for_stdp_solo__tmp;
  S_.a_pre__for_stdp_solo = a_pre__for_stdp_solo__tmp;
  V_.__h = old___h;
  recompute_internal_variables(true);

  return get_a_pre__for_stdp_solo();
}

double
iaf_psc_exp_wta__with_stdp_solo::get_a_post__for_stdp_solo( double t, const bool before_increment )
{
#ifdef DEBUG
  std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_post__for_stdp_solo: getting value at t = " << t << std::endl;
#endif

  // case when the neuron has not yet spiked
  if ( history_.empty() )
  {
#ifdef DEBUG
    std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_post__for_stdp_solo: \thistory empty, returning initial value = " << a_post__for_stdp_solo__iv << std::endl;
#endif
    // return initial value
    return a_post__for_stdp_solo__iv;
  }

  // search for the latest post spike in the history buffer that came strictly before `t`
  int i = history_.size() - 1;
  double eps = 0.;
  if ( before_increment ) {
   eps = nest::kernel().connection_manager.get_stdp_eps();
  }
  while ( i >= 0 )
  {
    if ( t - history_[ i ].t_ >= eps )
    {
#ifdef DEBUG
      std::cout<<"iaf_psc_exp_wta__with_stdp_solo::get_a_post__for_stdp_solo: \tspike occurred at history[i].t_ = " << history_[i].t_ << std::endl;
#endif
      S_.a_pre__for_stdp_solo = history_[ i ].a_pre__for_stdp_solo_;
      S_.a_post__for_stdp_solo = history_[ i ].a_post__for_stdp_solo_;

      /**
       * update state variables transferred from synapse from `history[i].t_` to `t`
      **/

      if ( t - history_[ i ].t_ >= nest::kernel().connection_manager.get_stdp_eps() )
      {
        const double old___h = V_.__h;
        V_.__h = t - history_[i].t_;
        assert(V_.__h > 0);
        recompute_internal_variables(true);
      /* generated by directives/AnalyticIntegrationStep_begin.jinja2 */
      double a_post__for_stdp_solo__tmp = V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo * get_a_post__for_stdp_solo();
      double a_pre__for_stdp_solo__tmp = V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo * get_a_pre__for_stdp_solo();
      /* replace analytically solvable variables with precisely integrated values  *//* generated by directives/AnalyticIntegrationStep_end.jinja2 */
      S_.a_post__for_stdp_solo = a_post__for_stdp_solo__tmp;
      S_.a_pre__for_stdp_solo = a_pre__for_stdp_solo__tmp;

        V_.__h = old___h;
        recompute_internal_variables(true);
      }

#ifdef DEBUG
      std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_post__for_stdp_solo: \treturning " << get_a_post__for_stdp_solo() << std::endl;
#endif
      return get_a_post__for_stdp_solo();       // type: double
    }
    --i;
  }

  // this case occurs when the trace was requested at a time precisely at that of the first spike in the history
  if ( (!before_increment) && t == history_[ 0 ].t_)
  {
    S_.a_pre__for_stdp_solo = history_[ 0 ].a_pre__for_stdp_solo_;
    S_.a_post__for_stdp_solo = history_[ 0 ].a_post__for_stdp_solo_;

#ifdef DEBUG
    std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_post__for_stdp_solo: \ttrace requested at exact time of history entry 0, returning " << get_a_post__for_stdp_solo() << std::endl;
#endif
    return get_a_post__for_stdp_solo();
  }

  // this case occurs when the trace was requested at a time before the first spike in the history
  // return initial value propagated in time
#ifdef DEBUG
  std::cout << "iaf_psc_exp_wta__with_stdp_solo::get_a_post__for_stdp_solo: \tfall-through, returning initial value = " << a_post__for_stdp_solo__iv << std::endl;
#endif

  if (t == 0.) {
    return 0.;  // initial value for convolution is always 0
  }

  // set to initial value
  S_.a_pre__for_stdp_solo = 0.;  // initial value for convolution is always 0
  S_.a_post__for_stdp_solo = 0.;  // initial value for convolution is always 0

  // propagate in time
  const double old___h = V_.__h;
  V_.__h = t;   // from time 0 to the requested time
  assert(V_.__h > 0);
  recompute_internal_variables(true);
  /* generated by directives/AnalyticIntegrationStep_begin.jinja2 */
  double a_post__for_stdp_solo__tmp = V_.__P__a_post__for_stdp_solo__a_post__for_stdp_solo * get_a_post__for_stdp_solo();
  double a_pre__for_stdp_solo__tmp = V_.__P__a_pre__for_stdp_solo__a_pre__for_stdp_solo * get_a_pre__for_stdp_solo();
  /* replace analytically solvable variables with precisely integrated values  *//* generated by directives/AnalyticIntegrationStep_end.jinja2 */
  S_.a_post__for_stdp_solo = a_post__for_stdp_solo__tmp;
  S_.a_pre__for_stdp_solo = a_pre__for_stdp_solo__tmp;
  V_.__h = old___h;
  recompute_internal_variables(true);

  return get_a_post__for_stdp_solo();
}