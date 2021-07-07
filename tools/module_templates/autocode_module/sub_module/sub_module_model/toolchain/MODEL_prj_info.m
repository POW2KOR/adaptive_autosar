%
% Sample project info is given below.
% Please adapt according to your models.
%

function info = prj_info
    info.project_name = 'dmc_alc_model';
    info.projectMainModel = 'X5ALC.slx';
    info.project_DD = 'X5ALC.dd';
    info.MainModelPath = '\dmc_alc_model\model\frame';
    info.DDPath = '\dmc_alc_model\toolchain\datadictionary';
    info.paraPath = '\dmc_alc_model\para';
    info.para_init = 'X5ALC_init.m';
    info.MatlabVer = '(R2020b)';
    info.TLVer = '5.1';
    info.AutocodeComponent = 'dmc';
    info.listbox_elements = {
        '[reference]->X5ALC/X5ALC_swc/Subsystem/X5ALC_swc/X5ALC/X5ALC_main/X5ALC/ALC_ObjectProcessing_BUS'
        '[reference]->X5ALC/X5ALC_swc/Subsystem/X5ALC_swc/X5ALC/X5ALC_main/X5ALC/ALC_InputProcessing_BUS'
        '[reference]->X5ALC/X5ALC_swc/Subsystem/X5ALC_swc/X5ALC/X5ALC_main/X5ALC/ALC_LCproposal_BUS'
        '[reference]->X5ALC/X5ALC_swc/Subsystem/X5ALC_swc/X5ALC/X5ALC_main/X5ALC/ALC_Statemachine_BUS'
        '[reference]->X5ALC/X5ALC_swc/Subsystem/X5ALC_swc/X5ALC/X5ALC_main/X5ALC/ALC_LateralControl_BUS'
        '[reference]->X5ALC/X5ALC_swc/Subsystem/X5ALC_swc/X5ALC/X5ALC_main/X5ALC/ALC_LongitudinalControl_BUS'
        '[reference]->X5ALC/X5ALC_swc/Subsystem/X5ALC_swc/X5ALC/X5ALC_main/X5ALC/OutputProcessing_Bus'
    };
