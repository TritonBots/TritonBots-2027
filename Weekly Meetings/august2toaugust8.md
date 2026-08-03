# Week of August 2 to August 8 meeting

## Agenda
Discuss team planning for the upcoming Fall 2026 quarter, recruiting, and updating the current team members on the new workflow


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



### Plan for AI
- Someone from AI should investigate networking issues from the competition
  - Still unresolved because we don't know the setup at the competition
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
    - I have posted Youtube links in Embedded channel, but the most of the team members are currently inactive or busy.
  - Create the block diagram for the Microcontroller and networking stack
    - I created one, and it's complete, but I will update it as we make design decisions.
  - Document the Arduino Uno R4 Wifi implementation
    - I have documented it in great detail.
  - Create specification control document for the STM32 and radio
    - I have not started on this, but I have done research on the radio and STM32 design in preparation.
  - Resarch networking and radio communication
    - I have pushed a research/network branch onto the repo with my current progress
- Pedro Pinela
  - Survey for interest by Monday
  - Meet with Diego and Rafa for Lead
  - Document dribbler and drivetrain
  - Get familiar with GitHub
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
