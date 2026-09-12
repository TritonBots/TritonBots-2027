# EE Onboarding Plan & Brainstorm

## Electrical Deadlines / Goals
* **Onboarding** (All complete by end of Week 1)
  * Finish onboarding slideset / notes by **9/6**
    * [Slides Link](https://docs.google.com/presentation/d/1oMNQWifCWxoK6HXGI8GxtlOc_9-duQmPTatCg5hIHgU/edit?usp=sharing)
  * Finish topics 2 and 4 by **9/13**
  * Finish application by **9/20**
  * Finish interviews and submission methods by **9/27**
  * Finish topic 3 by **10/4**
* **MK3 working** by end of week 3 (**10/10**)

### Goals
* **Cast a wider net of applicants:** EE will "train" roughly **15 people out of ~40 applicants** (example numbers).
* **Meeting Attendance:** New people must attend the **1st bi-weekly meeting** and at least **2 subteam meetings** during training. After finishing onboarding, they attend meetings like any regular member is expected to.
* **Hybrid Structure:** Onboarding will be a mix of fully virtual and in-person work:
  * **Week 1:** In person
  * **Weeks 2–3:** Virtual
  * **Week 4:** In person
* **Passive Filtering:** The goal is to passively filter out new people over roughly 3–4 weeks. Even if 15 are taken in, it's likely fewer than 5 will stay through the end of the quarter, and even fewer through the end of the year.
* **Commitment Device:** Could consider an initial donation as an extra commitment device if needed—but this would come back to them in the form of food or similar.

### Logistics
* Enroll new people in a **GitHub Classroom** where they can submit videos or files.
* The topics below will all be finalized into documents for review and studying.
* People who are let in will also **take quizzes** as minor checks that they actually read the material.

***

## Topic 1: Our Robot
Create a document covering the major components of our robot:
* Block diagram of the robot
* Slides for each of our PCBs
* Major design features or components
* Reasoning behind component or design choices
* Notes on the history or iterations
* **How we work with other subteams:**
  * Bi-weekly meetings
  * Weekly collaboration with Mechanical and Electrical on our designs
* Time expectations
* **Strike policy (possibly by subteam?):**
  * 3 strikes before a check-in?
  * 5 strikes before a warning?
  * 7 strikes and off the team?
  * *Strike reasons:*
    * Missing required meetings without notification
    * Causing conflict with other members for no reason
* Software needed to work

***

## Topic 2: Team Engineering Practices
* **SOP for design flow:** Idea -> Sourcing -> Creation -> Review
* **Project Requirements:** Complete a clear list of all project requirements, with input from Electrical and Embedded teams:
  * Features / Use cases
  * Voltage / Power requirements
  * Peripherals
  * Component sizes / Package sizing (what package size and why)
  * Design rules / Safety precautions
  * Possible risks (time delays, uncertainty in part selection, costs, etc.)
* **Sourcing:** Begin sourcing major components that fit requirements *before* any routing or schematics. Any new components must be added to the Altium component library.
  * *Processors* -> RAM, Hz, cores, ADCs
  * *Diodes* -> turn-on time, Vfwd, Vrb
  * *Prototyping:* Order small batches of components and test first (e.g., ICs). Example: you know you need a memory IC, but have no way to test it.
* **Layout:** Complete schematic and PCB layout, then get team review.
* **Testing guidance and documentation:**
  * Kinds of equipment available
  * Different kinds of tests (voltage, current)
  * Things to consider when designing a test procedure
  * Design a test procedure for situation X

***

## Topic 3: Datasheet and Altium Video Practice
* List of tutorial basics including hotkeys, tools, and sample boards (to be uploaded).
* Video of a PCB creation process to follow, putting the above standards into practice.
* Soldering of the demo PCB—important to let them practice soldering.
* Small test on reading a datasheet.
* **Execution Options:**
  * Start with basic Altium tutorial.
  * Give them an old PCB or something without the files and have them **reverse engineer it** (helps give practice with testing + datasheets).
  * Turn in the schematic + short explanation of main functionality and ICs.
  * *Note on Layout:* Maybe skip layout for time if it’s complicated/more than two layers. If we still want a layout component, provide a separate board where the schematic is already done and they just do a 2-layer layout.
  * *Alternative:* Pick a circuit from their classes (only makes sense if they’ve taken enough ECE classes).

***

## Topic 4: Freeplay (Final Stage)
* **Design your own PCB**—it's not that bad!
* **Requirements (Still to be defined):**
  * Bare minimum could include utilizing at least **ONE IC** and summarizing its functionality (shows if they read the datasheet).
  * Digital-based PCBs might be too hard for a short span. Recommend **analog** (basic op-amp circuit, maybe a filter) unless they are highly comfortable with digital.
  * Must implement **important testpoints** for effective debugging.
  * Use **Altium** or **KiCad**.
  * Write a basic paragraph explaining the fundamental function of the PCB.
* **Submission:** When ready, submit project files for review using **GitHub** to push the project files.
* *Timeline:* This part of training can extend multiple weeks, but ideally just **3–4 weeks**.

***

# Slideset Brainstorm & Checklist

## Work Weeks and Expectations
* **Week 10** should **not** be a crunch week.
* **Crunch Weeks:**
  * Weeks 1–3
  * Weeks 7–9
* **Time Commitment:** Given that meetings are twice a week -> **1–2 hours outside of meetings**.
* **Meeting Cadence:**
  * All Hands: Every week
  * Lead meetings: 1 a week
  * Subteam meetings: 1 a week minimum

## Attendance & Heads Up Policy
* **Attendance Policy:**
  * 3 missed all-hands without a heads up = penalty
  * 3 missed subteam meetings without a heads up = penalty
* **Heads Up Policy:** Must give notice at least **12 hours** in advance.
* **Series of Consequences:**
  1. Lead takes notice
  2. Lead checks in personally
  3. Lead brings it up to **THE COUNCIL**
  4. Likely removed from the team

***

## 📋 To-Do / Action Items

- [ ] **Block diagram of the robot**
- [ ] **Slides for each of our PCBs**
  - [ ] Major design features or components
  - [ ] Reasoning behind component or design choices
  - [ ] Notes on the history or iterations
- [ ] **Cross-Subteam Collaboration Documentation**
  - [ ] Mechanical
  - [ ] Embedded
  - [ ] Software
- [ ] **Meetings Schedule & Expectations**
  - [ ] Time expectations
  - [ ] Meetings tracker
- [ ] **Current Projects and Timeline**
  - [ ] Karaoke project
- [ ] **Tools and Skills Guides**
  - [ ] Altium
    - [ ] Schematic design
    - [ ] Component library
    - [ ] Layout
    - [ ] MCAD CoDesigner
    - [ ] Revision history

### Design Flow Process Checklist
- [ ] Pick a topic and research what goes into making it happen
- [ ] Meeting about PCB objectives and metrics to meet based on findings
- [ ] Delegate research tasks for actual components
- [ ] Team updates on findings (All components must be found before routing)
- [ ] **Design Review Process:** Run PCB reviews at schematic, component layout, routing, and final review stages.

### Onboarding Overview Checklist
- [ ] **Week 1:** Google form and screenshots
- [ ] **Week 2:** [TBD]
- [ ] **Week 3:** [TBD]
- [ ] **Week 4:** [TBD]

### Team Environment Goals
* 💡 **Learning Environment / Hands-on:** Focus on practical experience.
* ❓ **Ask Questions:** Cultivate a culture of curiosity.
* 🤝 **Transparency:** Be transparent with what you can and can’t do.
* 🎉 **Have fun!**