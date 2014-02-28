# source /uusoc/facility/cad_common/local/setups/F07/setup-synopsys
# pt_shell < postroute.tcl > postroute.tcl.log

#/uusoc/facility/cad_common/Synopsys/PTS-F09/bin/pt_shell < postroute.tcl > postroute.tcl.log

### This is the script for optimizing the verilog

set power_enable_analysis TRUE

#----------------------------------------------------------------------#
#                        DESIGN DEFINITION                             #
#----------------------------------------------------------------------#


set design_name  FFT_4
set design_dir   "."


### EDIT $design_name.cstr.tcl for timing and other constraints!



############## technology files #########################
### can include multiple .db files in string.

## UWashington 130nm:
#set lib_name  "static184cg_1.5V_25C"
#set lib_db    "static184cg_1.5V_25C.db"
#set lib_dir   "/uusoc/facility/cad_common/local/Cadence/lib/cg_lib13_v096/"
#set lib_pdb   physical db defs

## Artisan 130nm:
set lib_name  "scadv12_cmos10sf_rvt_tt_1v_25c"
set lib_db    "scadv12_cmos10sf_rvt_tt_1v_25c.db.ORIG"
set lib_dir   "/uusoc/facility/cad_common/Artisan/IBM10SF/rvt/aci/sc-ad12/synopsys/"
#set lib_pdb   "ibm13svt_8lm_2thick_3rf.pdb"

## Utah
#set lib_name  "UofU_Digital_v1_2"
#set lib_db    "UofU_Digital_v1_2.db"
#set lib_dir   "/uusoc/facility/cad_common/local/Cadence/lib/UofU_Digital_v1_2/"
## set lib_pdb   physical db defs

############# custom library files #############################
#set custom_cells ../lib/custom-cells.v
#set custom_seq   ../lib/custom-sequentials.v


################################################
#            DC configuration variables
# Milkyway related variables
set mw_design_library $design_name.mw
#set mw_power_net   VDD
#set mw_ground_net  VSS
set mw_logic1_net  VDD
set mw_logic0_net  VSS
set mw_power_port  VDD
set mw_ground_port VSS
##set mw_tech_file /.../milkyway/tcbn90ghphvt_130a/techfiles/tsmcn90_7lm_6x6.tf
##set mw_reference_library [list /../milkyway/tcbn90ghphvt_130a /../milkyway/tcbn90ghplvt_130a]


# db and cache configuration
set cache_read  {}
set cache_write {}
set allow_newer_db_files       true
set write_compressed_db_files  true
set sh_source_uses_search_path true
#################################################



#----------------------------------------------------------------------#
#                             DESIGN SETUP                             #
#----------------------------------------------------------------------#

set search_path [concat  . $design_dir $lib_dir $search_path]
set search_path "$search_path ${synopsys_root}/libraries/syn"
set search_path "$search_path ${synopsys_root}/dw/sim_ver"


################################################################
# DC library definitions
set local_link_library [list ]
set target_library $lib_db
#set target_library $lib_dir/$lib_db

set synthetic_library "dw_foundation.sldb"
set link_library [concat * $lib_db $synthetic_library]
#set link_library [concat * $lib_dir/$lib_db $synthetic_library]
if [info exists lib_pdb] {
    set physical_library $lib_pdb
} else {
    set physical_library [list ]
}

set symbol_library [list ]
################################################################


if [info exists dc_shell_mode] {
    set suppress_errors "$suppress_errors TRANS-1 TIM-111 TIM-164 OPT-109 UID-101 TIM-134 DDB-74"
}

#checkpoint setup

# ------------------------------------------------------------
# Read in Design
# ------------------------------------------------------------
# Read in netlist
read_file -f verilog FFT_4_APR.v
# Define top level in the hierarchy
current_design $design_name
# Combine verilog and db files and identify any errors.
link_design
# Read in SPEF file
read_sdc $design_name.dcopt.sdc
read_sdf FFT_4.sdf
report_annotated_delay
#For no parasitics report, comment the next line
current_design $design_name
#read_parasitics -syntax_only -format SPEF ../soc/protocol_4X.spef
read_parasitics -increment -format SPEF FFT_4.spef


#read_vcd $design_name.vcd -strip_path $design_name
#report_switching_activity -hierarchy > switching_activity.txt


update_power
check_timing -verbose
update_timing
#Read all timing path
source RT.timing.tcl
#report_timing -delay max -max_paths 1000 -nworst 1500 -significant_digits 3  -from [get_pins tk1_0/ra_] -to [get_pins tk1_0/rr_]
report_timing > timing_report.pt.txt
report_timing -true >> timing_report.pt.txt
report_constraint >> timing_report.pt.txt
report_disable_timing >> timing_report.pt.txt
check_power > power_postroute_report.pt.txt
#create_power_waveforms -output vcd_waveforms >> power_postroute_report.pt.txt
#For propagation debugging, you must first
#specify the update_power command
#update_power
#To provide information about nets driven by sequential
#cells that have zero toggles
#report_switching_activity -coverage -include_only sequential
#report_switching_activity -list_zero_activity -include_only sequential
report_power >> power_postroute_report.pt.txt
report_constraints -all_violators -verbose >> report_constraints.pt.txt
