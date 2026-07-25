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
  - [Networking basics](https://scalac.io/blog/networking-basics/)
  - [How Ethernet Sends Data - Computerphile](https://youtu.be/SJE2lFR5utM)
  - [STM32 Ethernet Explained — MAC, PHY, RMII, and Driver Implementation (with Mongoose)](https://youtu.be/6kHYvFjeuaQ)
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


- **The Basics of Networking: (Source: [Networking basics](https://scalac.io/blog/networking-basics/))**

  - Local Area Network (LAN) is a network of computers connected in a physical network of cables
  - Wireless Local Area Network (WLAN) is the same as LAN but connected by wireless signals
  - Wide Area Network (WAN) is a large network that spans a physically large area like the internet itself
  - Internet Protocol (IP) is used to communicate between networks by routing for the fastest way to send a packet.
  - IP is a logical address, so if a device is connected to multiple networks, it will have a unique IP address for each network.
  - Media Access Control (MAC) is a physical address of a computer that is permanent for the computer's network card. It is assigned by the manufacturer. MAC addresses are for communication within a network, like connecting to a printer at home.

   |IP|MAC|
   |---|---|
   |Logical Address|Physical Address|
   |Identifies connection with a device in the network|Identifies device in the network|
   |Assigned by the network administrator or ISP (internet service provider)|Assigned by the manufacturer|
   |Used in WAN communication|Used in LAN/WLAN communication|
   
   - Transmission Control Protocol (TCP) is a highly-reliable and connection-oriented protocol. It does a 3-way handshake before sending data. It sends a connection request (SYN), receives a "I'm ready to reply" (SYN/ACK), and it sends a "Ok, send it" (ACK). TCP will retransmit packets if any were dropped. TCP will send the packets out of order but will fix the order before sending it to the application. TCP is heavy but it has a reliable connection and never loses data packets.
   - User Datagram Protocol (UDP) is a communication protocol like TCP but it doesn't care about sending data in the correct order. It also has no handshake for establishing a connection. It simply sends packets very fast with little overhead (60% lighter packets compared to TCP). It is unreliable and loses packets but it's fast.
   - The rest of this article goes into great detail of Computer Networking in an area that is important but not very relevant to what we need to accomplish e.g. file transfering and email protocols.

- **How Ethernet sends Data: (Source: [How Ethernet Sends Data - Computerphile](https://youtu.be/SJE2lFR5utM))**

  - This video talks more about the individual bits and hurdles of communication protocols.
  - It's an informative video, but I was not able to find any particularly useful information.

- **Ethernet with STM32: (Source: [STM32 Ethernet Explained — MAC, PHY, RMII, and Driver Implementation (with Mongoose)](https://youtu.be/6kHYvFjeuaQ))**

  - The Ethernet controller on an STM32 have two parts: MAC and PHY controllers
  
  |MAC|PHY|
  |---|---|
  |Build & Parse Ethernet Frames|Emitting Data on the wire|
  |Reading/Writing frames to RAM|Link speed/duplex negotiation|
  |Frame checksumming|Reporting status to MAC|

  - STM32 has the MAC component built into the MCU and the PHY controller as a separate component
  - The STM32H723ZG uses an external LAN8742 PHY

  |Feature|MII (Media Independent Interface)|RMII (Reduced MII)|RGMII (Reduced Gigabit MII)|
  |---|---|---|---|
  |Max Speed|100 Mbps|100 Mbps| 1 Gbps|
  |Clock Source|Separate TX & RX clocks(25 MHz for 100 M)|Single 50 MHz reference clock|Single 125 MHz clock (DDR)|
  |Pin Count|18|9|14|
  |Complexity|High|Low|Medium|

  - The STM32H723ZG has all Ethernet Interfaces

  - Left off at 4:44
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