tests = [ 
    
    { # Test 1: Checks that LED 1 is on.
    'description': 'PINA: 0x00 => PORTB: 0x01',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1 },
               ],
    'expected': [('PORTB',0x01)],
    },
    
    { # Test 2: Checks that LED 2 is on.
    'description': 'PINA: 0x00 => PORTB: 0x02',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1 },
               ],
    'expected': [('PORTB',0x02)],
    },
    
    { # Test 3: Checks that LED 3 is on.
    'description': 'PINA: 0x00 => PORTB: 0x04',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1 },
               ],
    'expected': [('PORTB',0x04)],
    },

    { # Test 4: Checks that LED 1 is on.
    'description': 'PINA: 0x00 => PORTB: 0x01',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1 },
               ],
    'expected': [('PORTB',0x01)],
    },

]

watch = ['PINA', 'PORTB']
