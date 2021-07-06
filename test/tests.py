tests = [ 
    
    { # Test 1:
    'description': 'PINA: 0x00 => PORTB: 0x00',
    'steps': [ {'inputs': [('PINA',0x00)], 'iterations': 1 },
               ],
    'expected': [('PORTB',0x00)],
    },
     
]

watch = ['PINA', 'PORTB']
