workspace "ZK_Draven"
  configurations { "Debug", "Release" }
project"ZK_Draven"
  kind "ConsoleApp"
  language "C"
filter "configurations:Debug"
  sysincludedirs  {"$(VC_IncludePath)"}
  defines { "_IAR_", "__ICCARM__", "_Pragma(x)=", "__interrupt=" }
  forceincludes { "" }
  includedirs { "$PROJ_DIR$", "../APP", "../BSP", "../STM8S_Driver/inc", "../ProtoOS" }
  files { "../APP/app.c", "../APP/app.h", "../APP/main.c", "../APP/stm8s.h", "../APP/stm8s_conf.h", "../APP/stm8s_it.c", "../APP/stm8s_it.h", "../BSP/bsp_led.c", "../BSP/bsp_led.h", "../ProtoOS/lc-addrlabels.h", "../ProtoOS/lc-switch.h", "../ProtoOS/lc.h", "../ProtoOS/pt-sem.h", "../ProtoOS/pt.h" }
  vpaths {["APP"] = { "../APP/app.c" , "../APP/app.h" , "../APP/main.c" , "../APP/stm8s.h" , "../APP/stm8s_conf.h" , "../APP/stm8s_it.c" , "../APP/stm8s_it.h" } , ["BSP"] = { "../BSP/bsp_led.c" , "../BSP/bsp_led.h" } , ["Modbus"] = { "" } , ["RTOS"] = { "../ProtoOS/lc-addrlabels.h" , "../ProtoOS/lc-switch.h" , "../ProtoOS/lc.h" , "../ProtoOS/pt-sem.h" , "../ProtoOS/pt.h" } , ["STM8S_Driver"] = { "" } }
filter "configurations:Release"
  sysincludedirs  {"$(VC_IncludePath)"}
  defines { "NDEBUG", "_IAR_", "__ICCARM__", "_Pragma(x)=", "__interrupt=" }
  forceincludes { "" }
  includedirs { "" }
  files { "../APP/app.c", "../APP/app.h", "../APP/main.c", "../APP/stm8s.h", "../APP/stm8s_conf.h", "../APP/stm8s_it.c", "../APP/stm8s_it.h", "../BSP/bsp_led.c", "../BSP/bsp_led.h", "../ProtoOS/lc-addrlabels.h", "../ProtoOS/lc-switch.h", "../ProtoOS/lc.h", "../ProtoOS/pt-sem.h", "../ProtoOS/pt.h" }
  vpaths {["APP"] = { "../APP/app.c" , "../APP/app.h" , "../APP/main.c" , "../APP/stm8s.h" , "../APP/stm8s_conf.h" , "../APP/stm8s_it.c" , "../APP/stm8s_it.h" } , ["BSP"] = { "../BSP/bsp_led.c" , "../BSP/bsp_led.h" } , ["Modbus"] = { "" } , ["RTOS"] = { "../ProtoOS/lc-addrlabels.h" , "../ProtoOS/lc-switch.h" , "../ProtoOS/lc.h" , "../ProtoOS/pt-sem.h" , "../ProtoOS/pt.h" } , ["STM8S_Driver"] = { "" } }
premake.override(premake.vstudio.vc2010, "includePath", function(base,cfg)
   local dirs = premake.vstudio.path(cfg, cfg.sysincludedirs)
    if #dirs > 0 then
    premake.vstudio.vc2010.element("IncludePath", nil, "%s", table.concat(dirs, ";"))
    end
end)