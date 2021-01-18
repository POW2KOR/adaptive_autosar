# Software Update Client NVUpdate Adapter 

```plantuml

skinparam componentStyle uml2
skinparam ComponentBackgroundColor #828788
skinparam ComponentBorderColor #000000
skinparam ComponentFontColor #FFFFFF
skinparam ComponentStereotypeFontColor #FFFFFF
skinparam RectangleFontColor #FFFFFF
skinparam ArrowColor #000000
title "Software Update Client Plugin"

interface "SwdlPlugin" as swldplugin
component [Nvidia Drive Update Library] as nv
swldplugin - [Software Update Client NVUpdate Adapter] 

component [Software Update Client] as swuc

swuc-> swldplugin  : <<use>>
[Software Update Client NVUpdate Adapter]  -> nv : <<library calls>>


```