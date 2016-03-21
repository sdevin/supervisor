rostopic pub /initialpose geometry_msgs/PoseWithCovarianceStamped '{ header: { frame_id: \"/map\" }, pose: { pose: { position: { x: 4.0, y: 4.0 }, orientation: { x: 0, y: 0, z: -0.0, w: 1.0 } }, covariance: [ 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.25, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.06853891945200942, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 ] } }'

rosservice call /pdg/manage_stream "{morseHuman: false, niutHuman: false, groupHuman: false, mocapHuman: false, adreamMocapHuman: false, toasterSimuHuman: true, pr2Robot: true, spencerRobot: false, toasterSimuRobot: false, toasterSimuObject: true}" 

rosservice call /database/empty_database

rosservice call /toaster_simu/add_entity "{id: 'TABLE_4', name: 'TABLE_4', type: 'object', ownerId: ''}"
rosservice call /toaster_simu/set_entity_pose "{id: 'TABLE_4', ownerId: '', type: 'object', x: 4.8, y: 4.1, z: -0.1, roll: 0.0, pitch: 0.0, yaw: 0.0}"

rosservice call /toaster_simu/add_entity "{id: 'RED_CUBE', name: 'RED_CUBE', type: 'object', ownerId: ''}"
rosservice call /toaster_simu/set_entity_pose "{id: 'RED_CUBE', ownerId: '', type: 'object', x: 4.6, y: 3.6, z: 0.7, roll: 0.0, pitch: 0.0, yaw: 0.0}"

rosservice call /toaster_simu/add_entity "{id: 'GREEN_CUBE', name: 'GREEN_CUBE', type: 'object', ownerId: ''}"
rosservice call /toaster_simu/set_entity_pose "{id: 'GREEN_CUBE', ownerId: '', type: 'object', x: 4.7, y: 3.7, z: 0.7, roll: 0.0, pitch: 0.0, yaw: 0.0}"

rosservice call /toaster_simu/add_entity "{id: 'BLUE_CUBE', name: 'BLUE_CUBE', type: 'object', ownerId: ''}"
rosservice call /toaster_simu/set_entity_pose "{id: 'BLUE_CUBE', ownerId: '', type: 'object', x: 5.1, y: 4.5, z: 0.7, roll: 0.0, pitch: 0.0, yaw: 0.0}"

rosservice call /toaster_simu/add_entity "{id: 'BLACK_CUBE', name: 'BLACK_CUBE', type: 'object', ownerId: ''}"
rosservice call /toaster_simu/set_entity_pose "{id: 'BLACK_CUBE', ownerId: '', type: 'object', x: 5.2, y: 4.6, z: 0.7, roll: 0.0, pitch: 0.0, yaw: 0.0}"

rosservice call /toaster_simu/add_entity "{id: 'PLACEMAT_RED', name: 'PLACEMAT_RED', type: 'object', ownerId: ''}"
rosservice call /toaster_simu/set_entity_pose "{id: 'PLACEMAT_RED', ownerId: '', type: 'object', x: 4.8, y: 4.1, z: 0.7, roll: 0.0, pitch: 0.0, yaw: 0.0}"

rosservice call /toaster_simu/add_entity "{id: 'HERAKLES_HUMAN1', name: 'HERAKLES_HUMAN1', type: 'human', ownerId: ''}"
rosservice call /toaster_simu/set_entity_pose "{id: 'HERAKLES_HUMAN1', ownerId: '', type: 'human', x: 6.0, y: 4.1, z: 0.0, roll: 0.0, pitch: 0.0, yaw: 3.14}"

rosservice call /toaster_simu/add_entity "{id: 'rightHand', name: 'rightHand', type: 'joint', ownerId: 'HERAKLES_HUMAN1'}"
rosservice call /toaster_simu/set_entity_pose "{id: 'rightHand', ownerId: 'HERAKLES_HUMAN1', type: 'joint', x: 6.1, y: 4.45, z: 1.0, roll: 0.0, pitch: 0.0, yaw: 3.14}"

rosservice call /toaster_simu/add_entity "{id: 'base', name: 'base', type: 'joint', ownerId: 'HERAKLES_HUMAN1'}"
rosservice call /toaster_simu/set_entity_pose "{id: 'base', ownerId: 'HERAKLES_HUMAN1', type: 'joint', x: 6.0, y: 4.1, z: 0.0, roll: 0.0, pitch: 0.0, yaw: 3.14}"




rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'RED_CUBE', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'BLACK_CUBE', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'GREEN_CUBE', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'BLUE_CUBE', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'TABLE_4', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'TABLE_4', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'PLACEMAT_RED', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'PLACEMAT_RED', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"


rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'RED_CUBE', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'BLACK_CUBE', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'GREEN_CUBE', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'BLUE_CUBE', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'TABLE_4', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'TABLE_4', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'PLACEMAT_RED', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isReachableBy', propertyType: 'state', subProperty: '', subjectId: 'PLACEMAT_RED', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"


rosservice call /database/add_fact_to_agent "{fact: {property: 'isVisibleBy', propertyType: 'state', subProperty: '', subjectId: 'PR2_ROBOT', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isVisibleBy', propertyType: 'state', subProperty: '', subjectId: 'HERAKLES_HUMAN1', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"

rosservice call /database/add_fact_to_agent "{fact: {property: 'isVisibleBy', propertyType: 'state', subProperty: '', subjectId: 'PR2_ROBOT', targetId: 'HERAKLES_HUMAN1', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'isVisibleBy', propertyType: 'state', subProperty: '', subjectId: 'HERAKLES_HUMAN1', targetId: 'PR2_ROBOT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'HERAKLES_HUMAN1'}"


rosservice call /database/add_fact_to_agent "{fact: {property: 'type', propertyType: 'state', subProperty: '', subjectId: 'RED_CUBE', targetId: 'CUBE', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'type', propertyType: 'state', subProperty: '', subjectId: 'GREEN_CUBE', targetId: 'CUBE', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'type', propertyType: 'state', subProperty: '', subjectId: 'BLUE_CUBE', targetId: 'CUBE', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'type', propertyType: 'state', subProperty: '', subjectId: 'BLACK_CUBE', targetId: 'CUBE', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'type', propertyType: 'state', subProperty: '', subjectId: 'TABLE_4', targetId: 'SUPPORT', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
rosservice call /database/add_fact_to_agent "{fact: {property: 'type', propertyType: 'state', subProperty: '', subjectId: 'PLACEMAT_RED', targetId: 'AREA', subjectOwnerId: '', targetOwnerId: '', valueType: false, factObservability: 0.0, doubleValue: 0.0, stringValue: '', confidence: 0.0, time: 0, timeStart: 0, timeEnd: 0}, agentId: 'PR2_ROBOT'}"
