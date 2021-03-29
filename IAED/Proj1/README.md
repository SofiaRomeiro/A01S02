# KANBAN Board - C 
## Project Details 

### Components

#### Time : iniciated to zero (0)

#### Task :
> Each task as :
>> **An identifier** : int, between [0, 10 000]
>
>> **A description** : not empty string, 50 chars max (including white spaces and tabs)
>
>> **An user** : who does the task (can have one user or more)
>
>> **Activitie** : where the task belongs, max of 10
>>> Pre-built activities: TO DO, IN PROGRESS, DONE
>
>> **Duration of the task** : int > 0
>
>> **When the task started** : int > 0
>
> Elements and Details:
>> - Each task begins in TO DO activitie, time equals to zero
>
>> - When the task leaves TO DO, the timer initiates counting
>
>> - The tasks ID's are atributted based on the order they are created 

### Activitie
> Each activitie as :
>> Description : max 20 char (including white spaces and tabs), only in CAPS LOCK
>
>> Different tasks can belong to the same activitie and the same user or different users
>
>> A task iniciates always on TO DO, and once it leaves TO DO, it can't go back to it,
>> but it can go back from any activitie to another, except going back to TO DO.
>> **Ex.:** a task can go from TO DO to DONE and go back to IN PROGRESS
>
### User
>Each user as:
>> a username: string max 20 chars, without white spaces
>
>> Can exist a max of 50 users
>

### Functions
>
	displaymenu()
>
 Display Menu: Recebe x e devolve y
>
	newtask()
>
> - IN : t <<duracao>> <<descricao>>
>
	taskslist()
>
	timeadder()
>
	newuser()
>
	movetask()
>
	alltaskslist()
>
	addactivitie()
>
