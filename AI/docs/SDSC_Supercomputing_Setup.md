# SDSC Supercomputing Setup

Created by: Evan Chou
Created time: June 7, 2026 1:38 AM
Category: Onboarding Documentation
Last edited by: Evan Chou
Last updated time: June 7, 2026 2:16 AM

# **Initial Account Setup**

1. Receive your temporary password from the team lead.
2. Sign into the user portal: [https://users.scc.sdsc.edu/](https://users.scc.sdsc.edu/).
    1. If there is a Windows Security pop-up, cancel that and sign into the Rocky Identity Management page directly.
3. Open settings and reset your password.
4. Insert your SSH key into your account, located in ~/.ssh/id_ed25519. If you’ve never generated an SSH key on your computer, follow the code instructions below using Terminal (NOT WSL).
    
    ```bash
    ssh-keygen -t ed25519 -C "your_username" # The -C parameter is optional, as it is just for your record
    # Press Enter to save the key to the default location
    # Press Enter twice to ignore the paraphrasing questions
    
    cat ~/.ssh/id_ed25519.pub # To output the entire SSH key
    
    # Your SSH key has been generated, so copy and paste the full output line into the account settings accordingly.
    ```
    
5. Test the SSH key by entering the following SSH command into your terminal:
    
    ```bash
    ssh YOUR_USERNAME@132.249.248.230
    ```
    
    *Note: If permission is denied, you may have to wait 20 minutes for it to be processed and refreshed. If it has been a long time and you are still denied from the cluster, contact Supercomputing Club for assistance.*
    
6. After entering the cluster, you will be in your user directory /home/username. To access the AI Team codebase, you can ****do a cd /projects/robocup, where you should find our codebase which is also connected to the remote.

# VS Code Remote SSH

1. Open VS Code and install the Remote SSH extension if it has not already been installed.
2. Press Ctrl + Shift + P and search up Remote SSH: Connect to Host…
3. Press Add New SSH Host, and copy the same SSH command used to enter the cluster through terminal.
4. Once it’s added, follow Step 2 again to open up the list of configured hosts
5. Press 132.249.248.230 to open a new VS Code window connecting to the cluster remotely
6. If first entry through VS Code, press Linux when prompted to specify the OS
7. Once the bottom left blue tab says that it says SSH:132.249.248.230, that means you are connected to the cluster on the VS Code window. Next, press the folders tab and press Open Folder to open any folder/codebase in your /home/user directory.
8. To access our RoboCup folder, press the “..” option twice until you reach the base parent directory. Enter /projects/robocup and select OK to open the codebase folder.

# Documentation

For more documentation, specifically on how to submit computing jobs through their SLURM system, you can follow instructions specified here: [Quick Start | UCSD Supercomputing Club](https://docs.scc.sdsc.edu/en/public/guide/quick-start)