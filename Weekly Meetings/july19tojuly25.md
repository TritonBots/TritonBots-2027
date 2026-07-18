# Week of July 14 to July 18 Meeting

## Agenda
Discuss team and engineering management changes to the team for our success and efficient time management. Also discuss mistakes made at the competition

## Hardware Issues
- The kickers were not tested
- The peripheral bus was not tested
- CAN-FD cables were not assembled
- Dribblers were not fully assembled
- Dribblers PID had to be retuned because of dribbler gear backlash
- Changes to the orientation of the motors needed to be made so motors had to be recalibrated
- Dribblers PID had to be retuned
- Drivetrain motors had issues with communication
- Shell was not redesigned for quick disassembly
- Hard to configure and flash each robot
- Cable management was a nightmare
- Hard to turn off the robot
- LEDs were hard to see for debugging
- 2.4GHz Wifi is not the standard for league communication
- Arduino IDE was annoying, VS code version sometimes worked
- Not enough extension cords and sockets
- Could not evaluate robot performance

## Software Issues
- Wifi was terrible to implement
- Did not know full purpose of the ehternet cable 
- Buffer size for ethernet packets was too small (look into)
- No display to work with for the mac mini
- Did not test networking

### Changes
- Keep every subteam “in the loop” by switching to GitHub
  - Issues, comments, discussion
  - Everyone is able to see tasks and their updates
  - All files are accessible by team members
- Ask who is contributing during the summer and willing to dedicate sufficient time for 2026-2027
  - Send out survey
    - Establish expectations
    - See who is able to commit time in person
    - Gauge how much we need to recruit
  - Knowledge transfer over summer
  - Plan and goals for next year
    - Recruitment process
  - Any leftover design work
  - Reach out to potential new lead for them to prepare
  - Help out with embedded
    - Raymond, Gabe, and Pedro

- Establish how to do weekly updates and effective team meetings
  - Post agenda beforehand
  - Provide action items for each member
  - Make a .md doc in the repo for every team member to update each week of ongoing/completed tasks
  - Makes it easier to see who is actually doing work
  - Set concrete engineering goals and milestones
  - Prevent tunnel-vision goals

- Engineering Design Reviews
  - Every related subteam member is updated on design changes
  - E.g. AI and Embedded on networking changes

- Block Diagrams
  - Networking/Comms + Sensors
  - Power
  - Motor control
  - Hardware configuration/stack
  - Gameplay and vision system

### Engineering Design Process
- Background Research
  - Each team does research on general robot functions that relate to their discipline, this is done to find engineering projects to start
- Specification Control Document
  - Describes the overall functionality of and needs for a project, needed before starting any development
  - Overarching needs, do not describe specifically to a certain piece of hardware or solution
- Brainstorm solutions
  - Watch out for biases
  - Choose the optimal solution

### Plan for AI
- Someone from AI should investigate networking issues from the competition
- Collaborate with Sukhjeet for networking, scope of AI has been redefined to only gameplay
- Immeditate research on simulator, testing, and rules
  - Background research on simulator teams 
  - Documentation for game states and game controller so we know we are ready for testing
    - Check if all rules have been implemented 
- Consider laptop or other portable device to run gameplay software
  - Ideally have mobile display so AI can run on mac mini


## Action Items
- Raymond Rada 
  - Create template for SCD and research
  - Create the block diagrams for power and hardware configuration/stack
  - Document the operation of the kicker and the power distribution board
  - Create specification control document for the kicker and power distribution board
  - Start researching design for motherboard
    - CAN-FD with separate controller + transceiver or integrated controller on MCU
- Sukhjeet Sekhon
  - Give directions for how to get GitHub setup for all team members
  - Create the block diagram for the Microcontroller and networking stack
  - Create specification control document for the STM32 and radio
  - Resarch networking and radio communication
- Pedro Pinela
  - 
- Evan Chou
  - Finish up Booster Champions Competition with current AI Team members
  - Delegate documentation tasks to available AI Team members
  - Create document that verify game controller states and rules
  - Block diagram of gameplay, AI, and vision controller
  - Updating docmentation on SDSC (supercomputing) setup
- Yash Tandon
  - Create document for research on simulators and other teams' implementations in more detail
- Adnan 
  - Create read me for AI codebase
