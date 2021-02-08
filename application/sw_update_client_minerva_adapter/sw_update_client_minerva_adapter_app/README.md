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



The Interface shall be used with the following sequence of function calls
any transition in the state diagram is a legal next function call:
```plantuml

skinparam componentStyle uml2
skinparam ComponentBackgroundColor #828788
skinparam ComponentBorderColor #000000
skinparam ComponentFontColor #FFFFFF
skinparam ComponentStereotypeFontColor #FFFFFF
skinparam RectangleFontColor #FFFFFF
skinparam ArrowColor #000000
title "Software Update Client Plugin Interface flow"

[*] --> GetResumePosition
[*] --> Process
GetResumePosition --> Process
Process --> Process
Process --> Activate
Verify --> CleanUp
Process--> Revert
Verify-->Rollback
Activate-->Rollback
Activate --> Verify
GetResumePosition : optional to receive the resume position
Process : file or pipe with 0 or exact resume position
Activate : prepare to switch to new version on reset
Verify : check that everything is fine
Revert : abort the download
Rollback : undo the version switch
Rollback -->CleanUp
 CleanUp--> [*]
 Revert--> [*]
Rollback --> [*]


 ```
