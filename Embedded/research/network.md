# Embedded Networking

## 1. Research Question
> *How does Networking work with Embedded systems with a focus on STM32 hardware?*

---

## 2. Background & Context
Provide a brief overview of the topic. Answer:
- Embedded Networking is relevant for understanding the communication between our computers and the radio communication of the RoboCup robots.
- This will cover broad topics of how Networking works in general, on a small-scale, with robotics, with radio, and specifically Embedded Networking. 

---

## 3. Key Areas to Investigate
- **Area 1:** What is Networking?
- **Area 2:** How does Networking work on a small-scale?
- **Area 3:** How does Networking work with robotics?
- **Area 4:** How to use Networking with radio communication?
- **Area 5:** How does Networking connect to Embedded software?

---

## 4. Sources & References
List the sources consulted. Prioritize credibility:

- **Primary Sources:** Official documents, data, firsthand accounts
- **Secondary Sources:** 

  - [Computer Networking in 100 Seconds](https://youtu.be/keeqnciDVOo)
  - [STM32 Ethernet Explained — MAC, PHY, RMII, and Driver Implementation (with Mongoose)](https://youtu.be/6kHYvFjeuaQ)
  - []()
  - []()
  - []()
- **Internal Sources:** Institutional policies, internal documentation

> !! Verify all sources for accuracy and recency before citing. !!

---

## 5. Key Findings
Summarize what you found for each area of investigation:

- **What is Computer Networking: (Source: [Computer Networking in 100 Seconds](https://youtu.be/keeqnciDVOo))**
  - Computer Networking is how computers exchange information
  - It is abstracted into 7 systems based on the Open Systems Interconnection (OSI) Model
  - Bottom layer (1st) is the Physical Hardware layer, like cables
  - The top layer (7th) is the Application layer, like speakers or displays
  - HTTP is a top-layer protocol
  - 6th layer is the Presentation layer that translates streams of bits into a standard format for the application
  - 5th layer is the Session layer that handles the connection between two computers, like user authentication
  - 4th layer is the Transport layer which is built on the Transmission Control Protocol (TCP). It takes streams of data from one computer to the other by segmenting it into pieces so it arrives in the correct order through the network.
  - A packet is a unit of data and information about who sent the data.
  - The 3rd layer is the Network is where the transport layer receives its data in the form of packets. Here has the Internet Protocol (IP). Every computer in the network has a unique IP address like an ID. When a computer sends information over the network, it sends it in the form of an IP packet which has the IP address in the header. This process happens on a router or gateway which connects to the Data Link Layer (2nd).
  - The 2nd layer is the Data Link Layer. It connects one physical node to another node in a network through the Ethernet or WiFi protocols. 
- **Finding 2:** [Summary of discovery and its significance]
- **Finding 3:** [Summary of discovery and its significance]

---

## 6. Analysis & Interpretation
- What patterns or trends emerged?
- Are there any contradictions or gaps in the information?
- How do the findings relate to the original research question?

---

## 7. Conclusions
State your answer to the original research question based on the evidence gathered.

> **Bottom Line:** [One to two sentence takeaway]

---

## 8. Open Questions & Next Steps
- What remains unanswered?
- What follow-up research or actions are recommended?
- Who should be consulted for further clarity?

---

## 9. Notes & Caveats
- List any assumptions made during research
- Flag any information that is time-sensitive or unverified
- Note any limitations in scope or source availability
`