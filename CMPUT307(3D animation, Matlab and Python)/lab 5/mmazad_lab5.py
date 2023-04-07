import random

"""
Adapted from https://github.com/CalciferZh/AMCParser/blob/master/amc_parser.py
"""
def read_line(stream, idx):
    if idx >= len(stream):
        return None, idx
    line = stream[idx].strip().split()
    idx += 1
    return line, idx

def parse_amc(file_path):
    with open(file_path) as f:
        content = f.read().splitlines()

    for idx, line in enumerate(content):
        if line == ':DEGREES':
            content = content[idx+1:]
            break

    frames = []
    idx = 0
    line, idx = read_line(content, idx)
    assert line[0].isnumeric(), line
    EOF = False
    while not EOF:
        joint_degree = {}
        while True:
            line, idx = read_line(content, idx)
            if line is None or (len(line) == 0):
                EOF = True
                break
            if line[0].isnumeric():
                break
            joint_degree[line[0]] = [float(deg) for deg in line[1:]]
        frames.append(joint_degree)
    return frames

def concatMoCap(input_filenames, n_transition_frames, out_filename):
    '''
    concatenate the input MoCap files in random order, 
    generate n_transition_frames transition frames using interpolation between every two MoCap files, 
    save the result as out_filename.
      parameter:
        input_filenames: [str], a list of all input filename strings
        n_transition_frames: int, number of transition frames
        out_filename: output file name
      return:
        None
    '''
    input_motion_files = []
    
    for name in input_filenames: #parse all amc files and add them to a list
        item = parse_amc(name)
        input_motion_files.append(item)
    
    random.shuffle(input_motion_files)
    
    f_count = 1
    main_output = input_motion_files.pop(0) #initialise the output with the first from the list of amc
    
    while input_motion_files:
        current = input_motion_files.pop(0) #get the next set of frames
        final_frame_old = main_output[-1] #get the last frame from the current output
        first_frame_new = current[0] #get the first frame of the next amc file
        diff_by_transition = {}
        
        #from the 2 frames above calculate how much each paramater changes for each bone and divide by n_transition frames + 1
        for bone in final_frame_old.keys():
            diff_by_transition[bone] = []
            for transform in range(len(final_frame_old[bone])):
                increment = first_frame_new[bone][transform] - final_frame_old[bone][transform]
                increment = increment/(n_transition_frames+1)
                diff_by_transition[bone].append(increment)
        
        for i in range(n_transition_frames): #create n transition frames and append to main output
            new_t = {} #dict representing a frame
            
            for part in final_frame_old.keys(): #for each bone, add the value calcualted in diff_by_transition multiplied by frame number
                data_set = []
                for val in range(len(final_frame_old[part])):
                    value = final_frame_old[part][val] + ((i+1)*diff_by_transition[part][val])
                    data_set[part].append(value)
                new_t[part] = data_set
            
            main_output.append(new_t)

        main_output = main_output + current
    
    default_lines = ['#!OML:ASF H:\Terrain\Walking\May29\JustinRory\Justin.ASF', ':FULLY-SPECIFIED', ':DEGREES']
    #write the 3 default lines to the outfile
    with open(out_filename) as f:
        for line in default_lines:
            f.write("%s\n" % line)

    #write each frame with frame counts to the output file
    frame_count = 1
    with open(out_filename) as o:
        for frame in main_output:
            o.write("%d\n" % frame_count)
            for segment,data in frame.items(): #write the bone data
                o.write("%s:%s\n" % (segment, data))
            frame_count += 1
