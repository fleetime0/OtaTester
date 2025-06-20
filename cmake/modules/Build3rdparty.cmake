function(Build3rdparty)

include(BuildBoost)
include(BuildCommonAPI)
include(BuildCommonAPIVSomeip)
include(BuildVSomeip)
include(BuildJson)

BuildBoost()
BuildCommonAPI()
BuildVSomeip()
BuildCommonAPIVSomeip()
BuildJson()

endfunction()
